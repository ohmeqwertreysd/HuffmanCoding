cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)									
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(HuffmanLib)

add_library(FrequencyCounter FrequencyCounter.cpp)
add_library(HuffmanTree HuffmanTree.cpp)
add_library(HuffmanEncoder HuffmanEncoder.cpp)
add_library(HuffmanDecoder HuffmanDecoder.cpp)