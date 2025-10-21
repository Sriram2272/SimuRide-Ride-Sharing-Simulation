cmake_minimum_required(VERSION 3.10)
project(SimuRide++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(simuride
    src/main.cpp
    src/Dispatcher.cpp
    src/Router.cpp
)

target_include_directories(simuride PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(tests
    tests/test_core.cpp
)

add_executable(test_datastruct
    tests/test_datastruct.cpp
)

add_executable(test_hungarian
    tests/test_hungarian.cpp
)



target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
