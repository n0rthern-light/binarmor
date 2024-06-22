#pragma once

#include "../AddSectionCommand.hpp"
#include "core/modification/section/SectionQuery.hpp"

class CAddSectionHandler
{
    ISectionQuery* m_sectionQuery;
public:
    CAddSectionHandler(ISectionQuery* sectionQuery);
    void handle(const CAddSectionCommand& command);
};

