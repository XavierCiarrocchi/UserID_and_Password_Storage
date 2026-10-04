Make a large secure database of usernames and passwords with the ability to query it at ease

Now works ability to search usernames and get a password
Also ability to add new entries

## How to compile (CMake, recommended)

Prerequisites: CMake 3.20+, Ninja, and MinGW g++ (`gcc`/`g++` on PATH).

```powershell
# from root
cmake --preset debug  // or: cmake --preset release
cmake --build --preset debug
```

The executable is placed in `Builds`.

Notes:
- Open a fresh terminal after installing Ninja so it is on your PATH.
- If you change `CMakeLists.txt` or `CMakePresets.json`, just re-run the
  build command — Ninja re-configures automatically.
- Manual compile still works too:
  `g++ main.cpp ReadFile.cpp WriteRead.cpp -o main.exe`

---

## Roadmap: How to make this a legit, useful project

Right now this is an in-memory `unordered_map` backed by a plaintext
`data.txt` (username on line N, password on line N+1). That's a great
start, but not yet a "database engine." Below is the prioritized path to
get there:

### 1. Fix correctness first
- [ ] `Load()` opens with `std::ios::app` — should be `std::ios::in`.
  Appending on read is a bug and hides truncation issues.
- [ ] `Save()` opens with `std::ios::app` — every run duplicates the
  whole map to the end of the file. Switch to truncate + atomic
  rename (`write data.txt.tmp` -> `rename`), or append-only + compaction.
- [ ] `LookUpName()` uses `map[Name]` which inserts on miss. Use
  `find()` and return `optional<string>` / status code instead.
- [ ] Handle malformed input: odd line count, empty lines, duplicate keys.
- [ ] Add `DeleteData()` / update path (currently stubbed).

### 2. Stop storing plaintext passwords
- [ ] Hash + salt passwords (e.g. Argon2, bcrypt, or at minimum SHA-256
  + per-user salt). Never write raw passwords to disk.
- [ ] Zero sensitive buffers after use, restrict `data.txt` file
  permissions.

### 3. Define a real storage format
- [ ] v1: length-prefixed binary record (`[key_len][key][val_len][val]`)
  instead of newline-delimited text — faster parse, supports any bytes.
- [ ] v2: Append-only log + in-memory index + periodic compaction
  (Bitcask-style). This is the simplest "real" engine design.
- [ ] v3: Paged file + B-Tree / LSM-Tree if you want range scans and
  datasets larger than RAM.

### 4. Add a proper API / CLI
- [ ] Replace interactive `cin >> Search_Name` with subcommands:
  `db get <user>`, `db put <user>`, `db del <user>`, `db bench`.
- [ ] Return exit codes + machine-readable output for scripting.

### 5. Testing + CI
- [ ] Unit tests (Catch2 / GoogleTest): round-trip Save/Load,
  duplicate insert, miss lookup, corrupt file.
- [ ] Fuzz the loader with random/corrupt inputs.
- [ ] Sanitizers in a CMake preset: `-fsanitize=address,undefined`.
- [ ] GitHub Actions: build debug/release + run tests on push.

### 6. Concurrency + crash safety
- [ ] `shared_mutex` for concurrent reads / exclusive writes.
- [ ] WAL (write-ahead log) + `fsync` before ack, atomic commit via
  rename. Kill -9 test: no torn writes after restart.

---

## Benchmarking: how to do it

You can't claim "fast" without numbers. Measure these 4 things:

| What | Metric | Why it matters |
|------|--------|----------------|
| `Load()` throughput | MB/s + records/s | Startup time on large DB |
| `Save()` throughput | MB/s + records/s | Checkpoint / shutdown cost |
| `LookUpName()` latency | avg / p50 / p99 / max (ns) | Query path — use p99, not avg |
| Memory + file size | RSS (MB), bytes/record | Text vs binary format comparison |

### How to implement it (concrete plan)

1. **Use `std::chrono::high_resolution_clock`, not wall-clock guessing.**
   Warm up once, then time N iterations and divide. Disable CPU
   frequency scaling / close background apps for stable runs.

2. **Add a `bench` mode, e.g. `bench.cpp`:**
   ```cpp
   // pseudocode
   auto t0 = high_resolution_clock::now();
   Load(file, map);
   auto t1 = high_resolution_clock::now();
   // lookup bench: time 100k random hits + 10% misses
   for (auto& k : keys) LookUpName(k, map);
   auto t2 = high_resolution_clock::now();
   // print ns/op, ops/sec, p50/p99 (sort the per-op samples)
   ```
   Key detail: benchmark **hits and misses separately** — your current
   `operator[]` path is much slower on miss (inserts an empty string).

3. **Scale sweep:** run at 10K (now), 100K, 1M, 10M records. Plot
   time vs N. Hash map lookups should be ~flat O(1); Load/Save should
   be linear O(N). If it's superlinear, you're reallocating or
   rehashing — fix with `map.reserve(N)`.

4. **Compare formats:** bench current newline-text vs length-prefixed
   binary vs `mmap` read. Expect 2-5x Load speedup from binary alone.

5. **Use Google Benchmark for rigor** (nanobenchmark is fine to start):
   ```cmake
   # CMake: FetchContent googletest/googlebenchmark, add bench target
   add_executable(bench bench.cpp ReadFile.cpp WriteRead.cpp)
   target_link_libraries(bench benchmark::benchmark)
   ```
   It handles warmup, repetitions, statistics, and `--benchmark_format=json`
   for tracking regressions in CI.

6. **Track regressions:** save JSON output per commit
   (`Builds/bench_latest.json`), fail CI if p99 lookup or Load time
   regresses >10%.

Start with #2 (a 50-line chrono harness + scale sweep). That alone turns
this from "toy demo" into a project you can profile, optimize, and put
on a resume.
