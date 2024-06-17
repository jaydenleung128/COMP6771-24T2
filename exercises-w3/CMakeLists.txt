# ------------------------------------------------------------ #
# -------------- DO NOT TOUCH BELOW THIS LINE ---------------- #
# ------------------------------------------------------------ #

# this must be the first line of a CMake script.
# sets the lowerbound on what CMake version can be used.
cmake_minimum_required(VERSION 3.0...3.5)

# the name of this CMake project and what language it uses
# we could list more languages if we were using more.
project(COMP6771_LAB_001 LANGUAGES CXX)

# we use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# this is helpful for editors like VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# helpful compiler flags for gcc/clang
# the descriptions for these flags can be found on the GNU Compiler Collection's webpage.
add_compile_options(
  -Wall
  -Wextra
  -Werror
  -pedantic-errors
  -Wconversion
  -Wsign-conversion
  -Wdouble-promotion
  -Wcast-align
  -Wformat=2
  -Wuninitialized
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wdeprecated-copy-dtor
  -Wold-style-cast
  -Wzero-as-null-pointer-constant
  -Wsuggest-override
  -fstack-protector-strong
)

# debug builds should be compiled with sanitizers
# sanitizers are small libraries that check things like buffer overrun with minimal runtime overhead.
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")


# add the testing library Catch2
enable_testing()
add_library(catch2_main lib/catch2_main.cpp)
target_include_directories(catch2_main PUBLIC lib)
# link the library so that other programs can get it
link_libraries(catch2_main)

# ------------------------------------------------------------ #
# -------------- DO NOT MODIFY ABOVE THIS LINE --------------- #
# ------------------------------------------------------------ #

# 3.1

add_library(sort_descending src/3.1/sort_descending.cpp)
link_libraries(sort_descending)

add_executable(sort_descending_test src/3.1/sort_descending.test.cpp)
add_test(sort_descending_test sort_descending_test)

# 3.2

add_library(vsort src/3.2/vsort.cpp)
link_libraries(vsort)

add_executable(vsort_test src/3.2/vsort.test.cpp)
add_test(vsort_test vsort_test)

# 3.3

add_library(stats src/3.3/stats.cpp)
link_libraries(stats)

add_executable(stats_test src/3.3/stats.test.cpp)
add_test(stats_test stats_test)

# 3.4

add_library(invert src/3.4/invert.cpp)
link_libraries(invert)

add_executable(invert_test src/3.4/invert.test.cpp)
add_test(invert_test invert_test)

# 3.5

add_library(microbenchmark src/3.5/microbenchmark.cpp)
link_libraries(microbenchmark)

add_executable(microbenchmark_test src/3.5/microbenchmark.test.cpp)
add_test(microbenchmark_test microbenchmark_test)


