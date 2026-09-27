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
