#pragma once

#include "core/shared/attributes.hpp"
#include "defines.hpp"

namespace program::core::payload {
    class IPayload
    {
    public:
        virtual std::string id() const = 0;
        virtual program::core::shared::Architecture architecture() const = 0;
        virtual program::core::shared::Format format() const = 0;
        virtual std::vector<ImportRequirement_t> imports() const = 0;
        virtual std::vector<SectionData_t> data() const = 0;
        virtual std::vector<SectionProcedures_t> text() const = 0;
        virtual ~IPayload() { };
    };
}
