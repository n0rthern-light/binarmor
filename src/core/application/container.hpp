#ifndef CORE_APPLICATION_CONTAINER_HPP_
#define CORE_APPLICATION_CONTAINER_HPP_

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
                extern std::unique_ptr<IFileReader> fileReader;
                extern std::unique_ptr<CBinaryFileStateManager> binaryFileStateManager;
                namespace analysis {
                    extern std::unique_ptr<CAnalysisRunner> runner;
                }
            }

            void init(int argc, char** argv);
        }
    }
}

#endif // CORE_APPLICATION_CONTAINER_HPP_
