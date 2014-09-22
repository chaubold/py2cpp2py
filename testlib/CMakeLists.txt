
cmake_minimum_required(VERSION 2.8)
find_package( Boost REQUIRED COMPONENTS python serialization )

find_package( PythonInterp REQUIRED )

if(WIN32)
  GET_FILENAME_COMPONENT(PYTHON_PREFIX "${PYTHON_EXECUTABLE}" PATH)
  message(STATUS "PYTHON_PREFIX ${PYTHON_PREFIX}")
  find_library(PYTHON_LIBRARY
        NAMES python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}.lib
        HINTS "${PYTHON_PREFIX}/libs"
        NO_DEFAULT_PATH)
  set(PYTHON_LIBRARIES "${PYTHON_LIBRARY}" CACHE FILEPATH "the Python library")
  
  find_path(PYTHON_INCLUDE_DIRS
        NAMES Python.h
        HINTS "${PYTHON_PREFIX}/include"
        NO_DEFAULT_PATH)
  set(PYTHON_INCLUDE_DIRS "${PYTHON_INCLUDE_DIRS}" CACHE PATH "the Python include directory")
else()
  find_package( PythonLibs REQUIRED )
endif()

# include external headers as system includes so we do not have to cope with their warnings
include_directories( SYSTEM ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS}/python2.7 )

add_library(testlib SHARED main.cpp)
target_link_libraries(testlib ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )