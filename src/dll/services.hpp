#pragma once

#include <memory>

#include <shared/self_obfuscation/DynamicLinker.hpp>
#include <shared/memory/PatternScanner.hpp>

extern std::unique_ptr<CDynamicLinker> gDynamicLinker;
extern std::unique_ptr<CPatternScanner> gPatternScanner;

void initServices();
