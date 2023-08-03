cmake_minimum_required(VERSION 3.20)
project(pyzdepth)

set(CMAKE_CXX_STANDARD 11)


find_package(PythonInterp REQUIRED)
find_package(PythonLibs "${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}" REQUIRED )
if (PYTHONLIBS_FOUND)
    include_directories(${PYTHON_INCLUDE_DIRS})
    message("Using default python version: " ${PYTHONLIBS_VERSION_STRING})
endif()


find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)
find_package(zdepth REQUIRED)
find_package(zstd REQUIRED)


add_subdirectory(pyzdepth)