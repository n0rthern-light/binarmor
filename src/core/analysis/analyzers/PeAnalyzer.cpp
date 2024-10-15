#include "PeAnalyzer.hpp"
#include "../exceptions/UnsupportedFileException.hpp"
#include "../../format/pe/PeFormat.hpp"
#include "core/modification/ids.hpp"
#include <shared/value/AddressType.hpp>
#include <memory>
#include <shared/self_obfuscation/strenc.hpp>

using namespace program::core::file;

void CPeAnalyzer::analyze(const CBinary& binary, BinaryFileAttributes_t& attributes)
{
    if (attributes.format != Format::Windows_PE) {
        throw UnsupportedFileException(strenc("Not detected any supported file format"));
    }

    auto pe = CPeFormat(binary);

    attributes.arch = pe.architecture();
    attributes.type = pe.type();
    auto sections = pe.peSections();
    attributes.sectionCount = sections.size();
    auto importModules = pe.peImportModules();
    attributes.importedModuleCount = importModules.size();
    uint_8 importFuncCount = 0;
    for(const auto& mod : importModules) {
        auto functions = mod.second->peImports();
        importFuncCount += functions.size();
    }
    attributes.importedFunctionsCount = importFuncCount;
    attributes.entryPoint = pe.entryPoint();
    attributes.sizeOfBinary = CUnsigned{ pe.addressType() == AddressType::_32_BIT ? as_32(binary.size()) : as_64(binary.size()) };

    uint_auto sizeOfCode = 0;
    for(const auto& section : sections) {
        if (section->name() == program::core::modification::sectionName::MAIN) {
            attributes.isProtected = true;
        }

        if (section->name() != strenc(".text")) {
            continue;
        }

        sizeOfCode += section->rawSize();
    }

    attributes.sizeOfCode = CUnsigned{ pe.addressType() == AddressType::_32_BIT ? as_32(sizeOfCode) : as_64(sizeOfCode)};
}

