#pragma once

#include "core/shared/attributes.hpp"
#include "shared/types/defines.hpp"
#include "defines.hpp"

class IPayload
{
public:
    virtual bool supports(const Attributes_t& attributes) const = 0;
    virtual std::vector<ImportRef_t> requiredImports() const = 0;
    virtual byte_vec content() const = 0;
};

