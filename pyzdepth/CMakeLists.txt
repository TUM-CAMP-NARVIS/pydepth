pybind11_add_module(pyzdepth "zdepth_wrapper.cpp")
target_include_directories(pyzdepth PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_core)
target_link_libraries(pyzdepth PRIVATE zdepth::zdepth Eigen3::Eigen zstd::libzstd_static)