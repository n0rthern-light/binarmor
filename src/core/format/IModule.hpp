#ifndef CORE_FORMAT__I_MODULE_HPP_
#define CORE_FORMAT__I_MODULE_HPP_

#include "core/format/IImport.hpp"
#include <map>
#include <string>

class IModule;

typedef std::shared_ptr<IModule> module_ptr;
typedef std::map<std::string, module_ptr> module_map;

class IModule
{
public:
    virtual ~IModule() {};
    virtual std::string name() const = 0;
    virtual import_vec imports() const = 0;
};

#endif // CORE_FORMAT__I_MODULE_HPP_
