cmake_minimum_required(VERSION 3.24)
project(Algebra)

set(CMAKE_CXX_STANDARD 17)

add_executable(Algebra main.cpp Cycle.cpp Cycle.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(CycleTest Tests/CycleTest.cpp Cycle.cpp)
target_link_libraries(CycleTest gtest_main)

