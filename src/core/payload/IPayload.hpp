#pragma once

#include "core/assembler/defines.hpp"
#include "core/shared/attributes.hpp"
#include "defines.hpp"

using namespace binarmor::core::payload;

class IPayload
{
public:
    virtual std::string id() const = 0;
    virtual Architecture architecture() const = 0;
    virtual Format format() const = 0;
    virtual std::vector<ImportRequirement_t> requiredImports() const = 0;
    virtual std::vector<DataRequirement_t> requiredData() const = 0;
    virtual std::vector<Procedure_t> content() const = 0;
};

