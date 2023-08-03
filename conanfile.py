from conan import ConanFile
from conan.tools.system.package_manager import Apt
from conan.tools.files import apply_conandata_patches, collect_libs, copy, export_conandata_patches, get, rename, replace_in_file, rmdir, save

import os, sys
import sysconfig
from io import StringIO

class PyZDepthConan(ConanFile):
    python_requires = "camp_common/0.5@camposs/stable"
    python_requires_extend = "camp_common.CampCMakeBase"

    name = "pyzdepth"
    version = "0.0.1"

    description = "Python wrapper for zdepth"
    url = "https://github.com/TUM-CAMP-NARVIS/pyzdepth"
    license = "internal"

    settings = "os", "compiler", "build_type", "arch"

    # all sources are deployed with the package
    exports_sources = "pyzdepth/*", "CMakeLists.txt", "setup.py", "README.rst"

    def requirements(self):
        self.requires("eigen/3.4.0")
        self.requires("zdepth/0.2@camposs/stable")
        self.requires("python_dev_config/1.0@camposs/stable")
        self.requires("pybind11/2.10.1")

    def configure(self):
        pass

    def package_info(self):
        self.cpp_info.libs = collect_libs(self)
