cmake_minimum_required(VERSION 3.0.0)
project(game_of_life VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(game_of_life game_of_life.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_test(GAME_OF_LIVE game_of_life)
