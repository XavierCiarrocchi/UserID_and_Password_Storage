cmake_minimum_required(VERSION 3.20.0)
project(MinatureDatabaseEngine VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard — required for <string_view>, structured bindings, etc.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json for IntelliSense / clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Pull in project config from cmake/ directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)

add_executable(MinatureDatabaseEngine
  main.cpp
  ReadFile.cpp
  WriteRead.cpp
)

target_include_directories(MinatureDatabaseEngine PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_project_warnings(MinatureDatabaseEngine)

# Put built .exe next to your existing Builds/ folder layout
set_target_properties(MinatureDatabaseEngine PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Builds"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Builds"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Builds"
)

