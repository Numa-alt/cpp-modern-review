cmake_minimum_required(VERSION 3.16)

project(cpp-modern-review LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp-modern-review
    src/main.cpp
    src/item_manager/ItemManager.cpp
    src/device/TemperatureSensor.cpp
    src/device/Motor.cpp
)