#ifndef CORE_FORMAT__I_IMPORT_HPP_
#define CORE_FORMAT__I_IMPORT_HPP_

#include <memory>
#include <vector>

class IImport;

typedef std::shared_ptr<IImport> import_ptr;
typedef std::vector<import_ptr> import_vec;

class IImport
{
public:
    virtual ~IImport() { };
    virtual std::string name() const = 0;
};

#endif // CORE_FORMAT__I_IMPORT_HPP_
