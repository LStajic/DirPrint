cmake_minimum_required(VERSION 3.10)
project(MyProject)

find_package(SQLiteCpp REQUIRED)
find_package(SQLite3 REQUIRED)

# ▼▼▼ MUST SET THIS TO SEE HEADERS ▼▼▼
include_directories(
    ${PROJECT_SOURCE_DIR}/h
    ${SQLiteCpp_INCLUDE_DIRS}
    ${SQLITE3_INCLUDE_DIRS}
)
# ▼▼▼ List all source files here ▼▼▼
add_executable(my_app
    src/main.cpp
    src/directory_scanner.cpp
)

target_link_libraries(my_app
    PRIVATE
    SQLiteCpp
    ${SQLITE3_LIBRARIES}
)

# Compiler flags
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)