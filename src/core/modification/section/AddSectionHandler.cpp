#include "AddSectionHandler.hpp"
#include "core/attributes.hpp"
#include "core/format/pe/PeFormat.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <memory>

CAddSectionHandler::CAddSectionHandler(CBinaryFileStateManager* binaryFileManager): m_binaryFilesManager(binaryFileManager) { }

void CAddSectionHandler::handle(const CAddSectionCommand& command)
{
    auto binaryFile = m_binaryFilesManager->binaryFile(command.fileId());
     
    if (binaryFile == nullptr) {
        throw ModificationException(strenc("Binary file not found in memory"));
    }

    if (binaryFile->format() != Format::Windows_PE) {
        throw ModificationException(strenc("Unsupported binary file format for modification"));
    }

    if (binaryFile->arch() != Architecture::X86) {
        throw ModificationException(strenc("Unsupported binary file architecture for modification"));
    }

    auto pe = CPeFormat::create(binaryFile->modifiedBinary());

    pe->addSection(command.sectionId(), command.permissions());

    // dont use fucking repository/query pattern just simply access the core file objects etc.
    // omg what i ve done /XDDDDD
    // simply use format sections etc and just it k33p it simple okay :-)
}
