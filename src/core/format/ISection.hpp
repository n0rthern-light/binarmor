#ifndef CORE_FORMAT__I_SECTION_HPP_
#define CORE_FORMAT__I_SECTION_HPP_

#include "core/shared/BinaryPointer.hpp"
#include "core/shared/SectionPermissions.hpp"
#include <string>
#include <shared/value/Unsigned.hpp>

class ISection;

typedef std::shared_ptr<ISection> section_ptr;
typedef std::vector<section_ptr> section_vec;

class ISection {
public:
    virtual ~ISection() = default;

    virtual std::string name() const = 0;
    virtual CUnsigned baseAddress() const = 0;
    virtual size_t size() const = 0;
    virtual CBinaryPointer origin() const = 0;
    virtual CSectionPermissions permissions() const = 0;
};

#endif // CORE_FORMAT__I_SECTION_HPP_
