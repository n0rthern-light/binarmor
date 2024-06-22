#include "AddSectionHandler.hpp"
#include "core/modification/AddSectionCommand.hpp"
#include "core/modification/ModificationException.hpp"
#include "core/modification/section/SectionQuery.hpp"
#include "shared/self_obfuscation/strenc.hpp"

CAddSectionHandler::CAddSectionHandler(ISectionQuery* sectionQuery): m_sectionQuery(sectionQuery) { }

void CAddSectionHandler::handle(const CAddSectionCommand& command)
{
    auto section = m_sectionQuery->findById(command.fileId(), command.sectionId());

    if (section.has_value()) {
        throw ModificationException(strenc("Section already exists"));
    }

     
}
