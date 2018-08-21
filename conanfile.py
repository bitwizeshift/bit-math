#!/bin/env python3

"""
conanfile.py for Bit::math
"""

# The MIT License (MIT)
#
# Copyright (c) 2018 Matthew Rodusek
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#!/usr/bin/env python3

from conans import ConanFile, CMake, tools

def extract_cmake_version():
    import re

    try:
        content = tools.load("CMakeLists.txt")
        major   = re.search(".*BIT_MATH_VERSION_MAJOR ([0-9]+) .*", content).group(1)
        minor   = re.search(".*BIT_MATH_VERSION_MINOR ([0-9]+) .*", content).group(1)
        patch   = re.search(".*BIT_MATH_VERSION_PATCH ([0-9]+) .*", content).group(1)

        return "{}.{}.{}".format(major,minor,patch)
    except Exception:
        return None

class BitMathConan(ConanFile):
    name = "BitMath"
    version = extract_cmake_version()
    description = "A math library"
    author = "bitwizeshift"
    generators = "cmake"
    exports_sources = ("CMakeLists.txt",
                       "CMake/Templates/*.in",
                       "CMake/Modules/*.cmake",
                       "include/*",
                       "src/*",
                       "LICENSE.md",
                       "docs/CMakeLists.txt",
                       "docs/Doxyfile.in")
    url = "https://github.com/bitwizeshift/bit-math"
    license = "MIT License"
    options = {"install_docs" : [True,False],
               "shared" : [True,False]}
    default_options = "install_docs=False", "shared=False"
    settings = "cppstd", "os", "compiler", "build_type", "arch"

    def source(self):
        pass

    def build(self):
        pass

    def test(self):
        pass

    def package(self):
        cmake = CMake(self)
        cmake.definitions["BIT_MATH_COMPILE_HEADER_SELF_CONTAINMENT_TESTS"] = "OFF"
        cmake.definitions["BIT_MATH_COMPILE_UNIT_TESTS"] = "OFF"
        cmake.definitions["BIT_MATH_GENERATE_DOCS"] = "ON" if self.options.install_docs else "OFF"
        cmake.definitions["BIT_MATH_INSTALL_DOCS"]  = "ON" if self.options.install_docs else "OFF"
        cmake.configure()
        # If we have specified to build install_docs, install them
        if self.options.install_docs:
            cmake.build(target="math_docs")
        cmake.install()

        self.copy(pattern="LICENSE.md", dst="licenses")
        return

    def package_id(self):
        return
