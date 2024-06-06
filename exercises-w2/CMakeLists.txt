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

# 2.4

add_library(scale src/2.4/scale.cpp)
link_libraries(scale)

add_executable(scale_test src/2.4/scale.test.cpp)
add_test(scale_test scale_test)

# 2.5

add_library(mismatch src/2.5/mismatch.cpp)
link_libraries(mismatch)

add_executable(mismatch_test src/2.5/mismatch.test.cpp)
add_test(mismatch_test mismatch_test)


# 2.6

add_library(permutation src/2.6/permutation.cpp)
link_libraries(permutation)

add_executable(permutation_test src/2.6/permutation.test.cpp)
add_test(permutation_test permutation_test)

# 2.7

add_library(assortment src/2.7/assortment.cpp)
link_libraries(assortment)

add_executable(assortment_test src/2.7/assortment.test.cpp)
add_test(assortment_test assortment_test)

# 2.8


add_library(mixer src/2.8/mixer.cpp)
link_libraries(mixer)

add_executable(mixer_test src/2.8/mixer.test.cpp)
add_test(mixer_test mixer_test)