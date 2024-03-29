# CMakeLists.txt
# Copyright (c) 2023- 2024 IndoorJson
# Author: Kunlin Yu <yukunlin@syriusrobotics.com>
# Create Date: 2024/1/6

cmake_minimum_required(VERSION 3.15)
project(indoorjson3-cpp)

### C++ standard

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(WIN32)
    add_compile_definitions(NOMINMAX)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --coverage")

# json-schema-validator
find_package(nlohmann_json_schema_validator REQUIRED)

# libgeos
find_package(GEOS REQUIRED)
add_compile_definitions(USE_UNSTABLE_GEOS_CPP_API)
#add_compile_definitions(USE_NLOHMANN_FROM_GEOS)

# gtest
find_package(GTest REQUIRED)

# glog
find_package(glog REQUIRED)
if(WIN32)
    add_compile_definitions(GLOG_NO_ABBREVIATED_SEVERITIES)
endif()

### include

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_INCLUDE_PATH})

### source code
set(SOURCE_CODE
  src/serialization.cpp
  src/id_lookup.cpp
)

### library

add_library(${PROJECT_NAME} ${SOURCE_CODE})

### tests
enable_testing()

set(TEST_CASES
    test_create
    test_deserialization
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(TEST_RESOURCES "${CMAKE_CURRENT_BINARY_DIR}/resources")
add_definitions(-DTEST_RESOURCES="${TEST_RESOURCES}")

foreach(CASE ${TEST_CASES})
  add_executable(${CASE} tests/${CASE}.cpp)
  add_test(NAME ${CASE} COMMAND ${CASE})
  target_link_libraries(${CASE}
    ${PROJECT_NAME}
    GEOS::geos
    nlohmann_json::nlohmann_json
    nlohmann_json_schema_validator
    glog::glog
    GTest::GTest
  )
endforeach()
