cmake_minimum_required(VERSION 3.14)
# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(blackjack-counter)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES
    "src/*.cpp"
	"main.cpp"
)

# Unit tests
enable_testing()

# HandTest
add_executable(HandTest tests/unit/HandTest.cpp ${SOURCES})
target_link_libraries(HandTest GTest::gtest_main)
add_test(NAME HandTest COMMAND HandTest)

# ShoeTest
add_executable(ShoeTest tests/unit/ShoeTest.cpp ${SOURCES})
target_link_libraries(ShoeTest GTest::gtest_main)
add_test(NAME ShoeTest COMMAND ShoeTest)

# CardTest
add_executable(CardTest tests/unit/CardTest.cpp ${SOURCES})
target_link_libraries(CardTest GTest::gtest_main)
add_test(NAME CardTest COMMAND CardTest)

# PlayerTest
add_executable(PlayerTest tests/unit/PlayerTest.cpp ${SOURCES})
target_link_libraries(PlayerTest GTest::gtest_main)
add_test(NAME PlayerTest COMMAND PlayerTest)

# HumanPlayerTest
add_executable(HumanPlayerTest tests/unit/HumanPlayerTest.cpp ${SOURCES})
target_link_libraries(HumanPlayerTest GTest::gtest_main)
add_test(NAME HumanPlayerTest COMMAND HumanPlayerTest)

# GameEngineTest
add_executable(GameEngineTest tests/unit/GameEngineTest.cpp ${SOURCES})
target_link_libraries(GameEngineTest GTest::gmock_main GTest::gtest_main)
add_test(NAME GameEngineTest COMMAND GameEngineTest)

