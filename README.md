# indoorjson3-cpp
indoorjson3 serialization and desrialization library writen in c++14

# Introduction
A experimental project tring to redesign IndoorGML concept to make it easy to use. And add transport system support.

# Example
```json
{
  "properties": {
    "name": "indoorjson3-cpp"
    "labels": ["indoorgml", "GIS"],
    "language": ["English", "中文", "한국어"],
    "author": {
      "name": "Kunlin Yu"
      "email": "yukunlin@syriusrobotics.com",
    },
  },
  "cells": [
    {
      "$id": "c1",
      "properties": {
        "roomNumber": "1103"
      },
      "space": "POLYGON ((0 0, 1 0, 1 1, 0 1, 0 0))",
      "point": "POINT (0.5 0.5)"
    },
    {
      "$id": "c2",
      "properties": {
        "roomNumber": "1104"
      },
      "space": "POLYGON ((1 0, 2 0, 2 1, 1 1, 1 0))",
      "point": "POINT (1.5 0.5)"
    }
  ],
  "connections": [
    {
      "$id": "conn1-2",
      "properties": {
        "type": "door",
        "开放时间": "全天",
        "오픈 시간": "하루 종일"
      },
      "fr": "c1",
      "to": "c2",
      "bound": "LINESTRING (1 0, 1 1)",
      "curve": "LINESTRING (0.5 0.5, 1.5 0.5)"
    }
  ],
  "layers": [
    {
      "$id": "layer",
      "cells": ["c1", "c2"]
    }
  ],
  "rlineses": []
}
```

# Depedencies

## json-schema-validator/2.2.0
We use [json-schema-validator](https://github.com/pboettch/json-schema-validator) to define and validate the json string which uses [nlohmann/json](https://github.com/nlohmann/json)

## geos/3.12.0
We use [libgeos](https://github.com/libgeos/geos) to represent the Geometry of CellSpace and CellBoundary.

## glog/0.6.0
for logging

## gtest/1.14.0
for unit tests.

# Build
## install dependencies manually (Ubuntu 22.04)
1. install using apt
```bash
sudo apt install libglog
sudo apt install libgoogle-glog-dev
sudo apt install libgtest-dev
sudo apt install nlohmann-json3-dev
```
2. install from source code
    1. json-schema-validator

    No apt sources are available for it, so we need to build it from source code
    ```bash
    git clone https://github.com/pboettch/json-schema-validator.git
    cd json-schema-validator
    mkdir build
    cd build
    cmake ..
    make -j16
    make install
    ```

    2. libgeos

    The default libgeos version of Ubuntu 22.04 is libgeos 3.10.2 which is not stable enough so we better build if from the source code.
    ```bash
    git clone https://github.com/libgeos/geos.git
    cd geos
    git checkout 3.12.0
    mkdir build
    cd build
    cmake ..  -DBUILD_TESTING=OFF
    make -j16
    sudo make install
    ```

3. build indoorjson3-cpp
```bash
cd indoorjson3-cpp
mkdir build
cd build
cmake ..
make -j16
```


## install dependencies using conan (Ubuntu 22.04)
1. Install conan first https://conan.io/downloads

2. Use conan to prepare the dependencies and generate cmake files in "build" directory.
```bash
conan install . --output-folder=build --build=missing
```
3. Then use cmake to configure.
```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
4. Finally trigger build using make.
```bash
make -j16
```

## install dependencies using conan (Windows Visual Studio Community)
1. Install conan first https://conan.io/downloads

2. Use conan to prepare the dependencies and generate cmake files in "out/build" directory.
```bash
conan install . --output-folder=out/build --build=missing
```

3. Open indoorjson3-cpp directory using Visual Studio

4. Set CMakeSettings.json
```json
  "installRoot": "${projectDir}\\out\\install\\${name}",
  "cmakeCommandArgs": "-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release",
```
5. Finally trigger configuration and building using VS GUI.

