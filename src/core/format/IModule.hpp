#ifndef CORE_FORMAT__I_MODULE_HPP_
#define CORE_FORMAT__I_MODULE_HPP_

#include <map>
#include <string>

class IModule;

typedef std::shared_ptr<IModule> module_ptr;
typedef std::map<std::string, module_ptr> module_map;

class IModule
{
public:
    virtual ~IModule() {};
};

#endif // CORE_FORMAT__I_MODULE_HPP_
