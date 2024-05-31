#pragma once

#include "../file/IFileReader.hpp"
#include "../file/BinaryFileStateManager.hpp"
#include "../file/analysis/AnalysisRunner.hpp"

namespace program
{
    namespace core
    {
        namespace container
        {
            namespace file {
                extern std::shared_ptr<IFileReader> fileReader;
                extern std::shared_ptr<CBinaryFileStateManager> binaryFileStateManager;

                namespace analysis {
                    extern std::shared_ptr<CAnalysisRunner> runner;
                }
            }

            void init(int argc, char** argv);
        }
    }
}

