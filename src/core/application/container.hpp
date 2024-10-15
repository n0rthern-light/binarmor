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
#include "core/payload/PayloadProcessor.hpp"

namespace program
{
    namespace core
    {
        namespace container
        {
            namespace file {
                extern std::unique_ptr<program::core::file::IFileSystem> fileSystem;
                extern std::unique_ptr<program::core::file::CBinaryFileStateManager> binaryFileStateManager;
                namespace analysis {
                    extern std::unique_ptr<program::core::analysis::CAnalysisRunner> runner;
                }
            }

            namespace assembly {
                extern std::unique_ptr<program::core::assembler::IAssembler> assembler_x86;
                extern std::unique_ptr<program::core::assembler::IAssembler> assembler_x86_64;
                extern std::unique_ptr<program::core::assembler::IAssembler> assembler_arm64;
            }

            namespace payload {
                extern std::unique_ptr<program::core::payload::IPayloadProcessor> payloadProcessor;
            }

            namespace handler {
                extern std::unique_ptr<program::core::modification::section::CAddSectionHandler> addSectionHandler;
                extern std::unique_ptr<program::core::modification::bytes::CAddBytesHandler> addBytesHandler;
                extern std::unique_ptr<program::core::modification::bytes::CChangeBytesHandler> changeBytesHandler;
                extern std::unique_ptr<program::core::modification::import::CAddImportsHandler> addImportsHandler;
                extern std::unique_ptr<program::core::modification::encrypt::CEncryptOriginalImportsHandler> encryptOriginalImportsHandler;
                extern std::unique_ptr<program::core::modification::section::CInitializeMainProtectionSectionHandler> initializeMainProtectionSectionHandler;
                extern std::unique_ptr<program::core::modification::resize::CFixBinaryResizeHandler> fixBinaryResizeHandler;
            }

            void init(int argc, char** argv);
            void exit();
        }
    }
}

#endif // CORE_APPLICATION_CONTAINER_HPP_
