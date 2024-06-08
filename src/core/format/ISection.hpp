#ifndef SRC_CORE_FORMAT__I_SECTION_HPP_
#define SRC_CORE_FORMAT__I_SECTION_HPP_





#include <string>
#include <shared/value/Unsigned.hpp>

class ISection {
public:
    virtual ~ISection() = default;

    virtual std::string name() const = 0;
	virtual CUnsigned baseAddress() const = 0;
    virtual size_t size() const = 0;
};




#endif // SRC_CORE_FORMAT__I_SECTION_HPP_
