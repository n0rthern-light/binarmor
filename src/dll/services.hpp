#ifndef SERVICES_H
#define SERVICES_H

#include <memory>

#include "../shared/DynamicLinker.hpp"
#include "../shared/PatternScanner.hpp"

extern std::unique_ptr<CDynamicLinker> gDynamicLinker;
extern std::unique_ptr<CPatternScanner> gPatternScanner;

void initServices();

#endif