#pragma once

#include "core/payload/IPayload.hpp"
#include "core/shared/attributes.hpp"
#include <vector>

class PeX86SplashPayload : public IPayload
{
    bool supports(const Attributes_t& attributes) const
    {
        return attributes.format == Format::Windows_PE && attributes.architecture == Architecture::X86;
    }

    std::vector<ImportRef_t> requiredImports() const
    {
        return { };
    }

    byte_vec content() const
    {
        return {
            
        };
    }
};
