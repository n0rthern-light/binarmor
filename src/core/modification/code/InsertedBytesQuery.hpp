#pragma once

#include <optional>
#include "InsertedBytes.hpp"
#include "shared/value/Uuid.hpp"

class IInsertedBytesQuery
{
public:
    virtual ~IInsertedBytesQuery() { }
    virtual std::optional<CInsertedBytes> findById(const file_id&, const CUuid& insertedBytesId) = 0;
    virtual std::vector<CInsertedBytes> findAllBySectionId(const file_id&, const CUuid& sectionId) = 0;
};
