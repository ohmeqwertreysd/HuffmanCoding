cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME HuffmanCoding)
project(${PROJECT_NAME})

set(SOURCES 
    main.cpp
)

include_directories(src)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
	FrequencyCounter 
	HuffmanTree
	HuffmanEncoder
	HuffmanDecoder
)

SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)