#pragma once

#include <optional>
#include "Section.hpp"

class ISectionQuery
{
public:
    virtual ~ISectionQuery() { }
    virtual std::optional<CSection> findById(const file_id&, const section_id& sectionId) = 0;
};
