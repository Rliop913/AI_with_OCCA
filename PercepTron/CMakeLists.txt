set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.5.0)
project(PTron VERSION 0.1.0 LANGUAGES C CXX)

find_package(OCCA REQUIRED)

set(dataSrc
${CMAKE_SOURCE_DIR}/dataset/data_reader.cpp
${CMAKE_SOURCE_DIR}/model/Perceptron.cpp

)

add_executable(PTron ${dataSrc} main.cpp)

target_include_directories(PTron PRIVATE
${CMAKE_SOURCE_DIR}/dataset
${CMAKE_SOURCE_DIR}/model

)

target_link_libraries(PTron PRIVATE
OCCA::libocca
)
