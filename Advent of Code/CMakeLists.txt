cmake_minimum_required(VERSION 3.31)
project(AOC)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*.cpp)
list(FILTER CPP_FILES INCLUDE REGEX "^[0-9]+/")

foreach(CPP_FILE IN LISTS CPP_FILES)
    get_filename_component(FILE_DIR ${CPP_FILE} DIRECTORY)
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
    
    string(REPLACE "/" "_" TARGET_NAME "${FILE_DIR}_${FILE_NAME}")
    string(REPLACE " " "_" TARGET_NAME "${TARGET_NAME}")
    
    add_executable(${TARGET_NAME} ${CPP_FILE})
    
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${FILE_DIR}"
        OUTPUT_NAME "${FILE_NAME}"
    )
    
    set(INPUT_FILE "${CMAKE_SOURCE_DIR}/${FILE_DIR}/${FILE_NAME}.input.txt")
    if(EXISTS ${INPUT_FILE})
        configure_file(${INPUT_FILE} "${CMAKE_BINARY_DIR}/${FILE_DIR}/${FILE_NAME}.input.txt" COPYONLY)
    endif()
endforeach()
