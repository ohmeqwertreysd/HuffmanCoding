cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)									
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(HuffmanTree)

add_library(FrequencyCounter FrequencyCounter.cpp FrequencyCounter.h)
add_library(HuffmanTree HuffmanTree.cpp HuffmanTree.h)
add_library(HuffmanEncoder HuffmanEncoder.cpp HuffmanEncoder.h)
add_library(HuffmanDecoder HuffmanDecoder.cpp HuffmanDecoder.h)