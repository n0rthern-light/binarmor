from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("openssl/3.2.2")
        self.requires("asmjit/cci.20240531")

    def layout(self):
        cmake_layout(self)

