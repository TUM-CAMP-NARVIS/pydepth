file(GLOB_RECURSE PYZDEPTH_SOURCES
        _core/**.cpp
        _core/**.h
)
pybind11_add_module(_core ${PYZDEPTH_SOURCES})
target_include_directories(_core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_core)
target_link_libraries(_core PRIVATE zdepth::zdepth Eigen3::Eigen zstd::libzstd_static)