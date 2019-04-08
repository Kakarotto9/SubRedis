cmake_minimum_required(VERSION 2.8)

project(SubRedis)
set(CMAKE_SUB_STANDARD 11)

file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SOURCES src/*.h src/*.cpp)

add_library (SubRedis SHARED ${SOURCES})
target_link_libraries(SubRedis hiredis)

install(TARGETS SubRedis DESTINATION /usr/local/lib)
install(FILES ${HEADERS} DESTINATION /usr/local/include/subredis)
