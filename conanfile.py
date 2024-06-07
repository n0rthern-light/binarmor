from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.gnu import Autotools, AutotoolsToolchain
from conan.tools.apple import is_apple_os

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("openssl/3.2.2")

    def generate(self):
        tc = AutotoolsToolchain(self)
        if is_apple_os(self):
            tc.extra_cflags.append("-arch x86_64 -arch arm64")
        tc.generate()

    def layout(self):
        cmake_layout(self)

