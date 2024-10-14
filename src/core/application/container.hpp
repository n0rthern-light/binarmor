#ifndef CORE_APPLICATION_CONTAINER_HPP_
#define CORE_APPLICATION_CONTAINER_HPP_

#include "../file/BinaryFileStateManager.hpp"
#include "../analysis/AnalysisRunner.hpp"
#include "../assembler/Assembler.hpp"
#include "core/file/IFileSystem.hpp"
#include "core/modification/bytes/AddBytesHandler.hpp"
#include "core/modification/bytes/ChangeBytesHandler.hpp"
#include "core/modification/import/AddImportsHandler.hpp"
#include "core/modification/import/EncryptOriginalImportsHandler.hpp"
#include "core/modification/resize/FixBinaryResizeHandler.hpp"
#include "core/modification/section/AddSectionHandler.hpp"
#include "core/modification/section/InitializeMainProtectionSectionHandler.hpp"
#include "core/payload/processor/PayloadProcessor.hpp"

using namespace program::core;

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
                extern std::unique_ptr<CChangeBytesHandler> changeBytesHandler;
                extern std::unique_ptr<modification::import::CAddImportsHandler> addImportsHandler;
                extern std::unique_ptr<modification::encrypt::CEncryptOriginalImportsHandler> encryptOriginalImportsHandler;
                extern std::unique_ptr<CInitializeMainProtectionSectionHandler> initializeMainProtectionSectionHandler;
                extern std::unique_ptr<CFixBinaryResizeHandler> fixBinaryResizeHandler;
            }

            void init(int argc, char** argv);
            void exit();
        }
    }
}

#endif // CORE_APPLICATION_CONTAINER_HPP_
