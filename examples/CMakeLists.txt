cmake_minimum_required(VERSION 2.8)

project(SubRedisTests)
set(CMAKE_SUB_STANDARD 11)

add_executable(asyncexample asyncexample.cpp)
add_executable(pipeliningexample pipeliningexample.cpp)
add_executable(safeexample safeexample.cpp)
add_executable(syncexample syncexample.cpp)

target_link_libraries(asyncexample hiredis)
target_link_libraries(asyncexample SubRedis)
target_link_libraries(asyncexample ev)

target_link_libraries(safeexample hiredis)
target_link_libraries(safeexample SubRedis)
target_link_libraries(safeexample pthread)

target_link_libraries(syncexample hiredis)
target_link_libraries(syncexample SubRedis)

target_link_libraries(pipeliningexample hiredis)
target_link_libraries(pipeliningexample SubRedis)
