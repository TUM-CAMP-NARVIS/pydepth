#define ZDEPTH_BUILD_STATIC
#include "zdepth.hpp"


#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>


PYBIND11_MAKE_OPAQUE(std::vector<uint16_t>);
PYBIND11_MAKE_OPAQUE(std::vector<uint8_t>);

namespace py = pybind11;

PYBIND11_MODULE(pyzdepth, m)
{

    py::bind_vector<std::vector<uint8_t>>(m, "VectorUInt8");
    py::bind_vector<std::vector<uint16_t>>(m, "VectorUInt16");

    py::enum_<zdepth::DepthResult> (m, "DepthResult")
        .value("FileTruncated", zdepth::DepthResult::FileTruncated)
        .value("WrongFormat", zdepth::DepthResult::WrongFormat)
        .value("Corrupted", zdepth::DepthResult::Corrupted)
        .value("MissingPFrame", zdepth::DepthResult::MissingPFrame)
        .value("BadDimensions", zdepth::DepthResult::BadDimensions)
        .value("Success", zdepth::DepthResult::Success)
        .export_values();

    m.def("IsDepthFrame", zdepth::IsDepthFrame);
    m.def("IsKeyFrame", zdepth::IsKeyFrame);


    m.def("AzureKinectQuantizeDepth", zdepth::AzureKinectQuantizeDepth);
    m.def("AzureKinectDequantizeDepth", zdepth::AzureKinectDequantizeDepth);
    m.def("QuantizeDepthImage", zdepth::QuantizeDepthImage);
    m.def("DequantizeDepthImage", zdepth::DequantizeDepthImage);
    m.def("ZstdCompress", zdepth::ZstdCompress);
    m.def("ZstdDecompress", zdepth::ZstdDecompress);
    m.def("Pad12", zdepth::Pad12);
    m.def("Pack12", zdepth::Pack12);
    m.def("Unpack12", zdepth::Unpack12);

    auto pyDepthCompressor = py::class_<zdepth::DepthCompressor>(m,"DepthCompressor");
    pyDepthCompressor
        .def(py::init<>())
        .def("Compress",[](zdepth::DepthCompressor &c,
                int width,
                int height,
                std::vector<uint16_t>& unquantized_depth,
                bool keyframe) {
            std::vector<uint8_t> compressed;
            auto result = c.Compress(width, height, &(unquantized_depth[0]), compressed, keyframe);
            return py::make_tuple(result, compressed);
        })
        .def("Decompress",[](zdepth::DepthCompressor &c,
                             std::vector<uint8_t>& compressed,
                             int width,
                             int height) {
            std::vector<uint16_t> depth_out;
            auto result = c.Decompress(compressed, width, height, depth_out);
            return py::make_tuple(result, depth_out);
        });

}