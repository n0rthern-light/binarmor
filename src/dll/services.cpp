#include "services.hpp"
#include <shared/self_obfuscation/win_api.hpp>

std::unique_ptr<CDynamicLinker> gDynamicLinker;
std::unique_ptr<CPatternScanner> gPatternScanner;

void initServices()
{
    gDynamicLinker = std::make_unique<CDynamicLinker>();
    gPatternScanner = std::make_unique<CPatternScanner>(gDynamicLinker.get());
};
