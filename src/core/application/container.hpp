#ifndef CORE_APPLICATION_CONTAINER_HPP_
#define CORE_APPLICATION_CONTAINER_HPP_

#include "../file/BinaryFileStateManager.hpp"
#include "../analysis/AnalysisRunner.hpp"
#include "../assembler/Assembler.hpp"
#include "core/file/IFileSystem.hpp"
#include "core/modification/bytes/AddBytesHandler.hpp"
#include "core/modification/section/AddSectionHandler.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"

namespace program
{
    namespace core
    {
        namespace container
        {
            namespace file {
                extern std::unique_ptr<IFileSystem> fileSystem;
                extern std::unique_ptr<CBinaryFileStateManager> binaryFileStateManager;
                namespace analysis {
                    extern std::unique_ptr<CAnalysisRunner> runner;
                }
            }

            namespace assembly {
                extern std::unique_ptr<IAssembler> assembler_x86;
                extern std::unique_ptr<IAssembler> assembler_x86_64;
                extern std::unique_ptr<IAssembler> assembler_arm64;
            }

            namespace payload {
                extern std::unique_ptr<IPayloadProcessor> payloadProcessor;
            }

            namespace handler {
                extern std::unique_ptr<CAddSectionHandler> addSectionHandler;
                extern std::unique_ptr<CAddBytesHandler> addBytesHandler;
            }

            void init(int argc, char** argv);
            void exit();
        }
    }
}

#endif // CORE_APPLICATION_CONTAINER_HPP_
