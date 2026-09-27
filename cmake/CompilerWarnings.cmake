# Compiler warnings for MinatureDatabaseEngine.
# Usage in root CMakeLists.txt:
#   include(cmake/CompilerWarnings.cmake)
#   set_project_warnings(MinatureDatabaseEngine)

function(set_project_warnings target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()
