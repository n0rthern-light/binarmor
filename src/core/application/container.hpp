#ifndef CORE_APPLICATION_CONTAINER_HPP_
#define CORE_APPLICATION_CONTAINER_HPP_

#include "../file/IFileReader.hpp"
#include "../file/BinaryFileStateManager.hpp"
#include "../analysis/AnalysisRunner.hpp"
#include "../assembler/Assembler.hpp"

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

            namespace assembly {
                extern std::unique_ptr<IAssembler> assembler;
            }

            void init(int argc, char** argv);
        }
    }
}

#endif // CORE_APPLICATION_CONTAINER_HPP_
