cmake_minimum_required(VERSION 2.6)
project(Rubix)

add_definitions(-DDEBUG)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -g")
set(EMSCRIPTEN 0)



set(POSTFIX "")
set(HEADER_FILES "${PROJECT_SOURCE_DIR}/src/")
set(SOURCE_FILES main.cpp )
set(DATA_FILES "CMakeLists.txt")
set(LIBRARIES)
set(ENGINE_PATH "${PROJECT_SOURCE_DIR}/../KTEngine/")
set(HEADER_FILES  ${HEADER_FILES} )
set(LIBRARIES ${LIBRARIES} )
set(SOURCE_FILES ${SOURCE_FILES} )


add_subdirectory(${ENGINE_PATH} KTEngine)


IF(EMSCRIPTEN)
    message(FATAL_ERROR "EMSCRIPTEN BUILD")
    add_definitions(-DRESOURCE_PATH="Resources/")
    set(HEADER_FILES ${HEADER_FILES} "/home/kevin/Desktop/emsdk_portable/emscripten/master/system/include/" "/home/kevin/Desktop/emsdk_portable/emscripten/master/tests/freetype/" "/home/kevin/Desktop/emsdk_portable/emscripten/master/tests/freetype/include/" "/usr/local/include/")
    SET(POSTFIX ".bc")
ELSE(EMSCRIPTEN)
    add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/Resources/")
ENDIF(EMSCRIPTEN)

add_subdirectory(src)

include_directories( ${HEADER_FILES} )

set_source_files_properties("CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(Rubix${POSTFIX} ${SOURCE_FILES} ${DATA_FILES})
target_link_libraries(Rubix${POSTFIX} ${LIBRARIES})