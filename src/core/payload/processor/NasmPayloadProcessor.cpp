#include "core/payload/processor/NasmPayloadProcessor.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/AddImportsCommand.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/defines.hpp"
#include "core/payload/processor/NasmData.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/algo/DependencyGraph.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include <cassert>
#include <format>
#include <memory>
#include <string>
#include <vector>

using namespace program::core::payload::nasm;
using namespace program::core::modification;

 const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::processImports(const file_id& fileId, const IPayload* payload) const
{
    const auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);
    auto imports = import::import_pair_vec_t { };

    for(const auto& requiredImport : payload->imports()) {
        const auto& import = fileFormat->import(requiredImport.moduleName, requiredImport.functionName);
        if (import == nullptr) {
            imports.push_back({requiredImport.moduleName, requiredImport.functionName});
        }
    }

    if (imports.empty() == true) {
        return nullptr;
    }

    return std::make_shared<import::CAddImportsCommand>(fileId, imports);
}

const CDependencyGraph CNasmPayloadProcessor::buildDependencyGraph(const file_id& fileId, const IPayload* payload) const
{
    const auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    auto dependencyGraph = CDependencyGraph { };

    // data
    for(const auto& section : payload->data()) {
        for(const auto& sectionData : section.data) {
            const auto nasmData = CNasmData { section.sectionName, sectionData };
            const auto dataId = nasmData.dataId(payload->id());
            const auto dependencies = nasmData.dependencies();

            if (dependencies.size() == 0) {
                dependencyGraph.addDependency(dataId, std::nullopt);
            } else {
                for(const auto& dependency : dependencies) {
                    dependencyGraph.addDependency(dataId, dependency);
                }
            }
        }
    }
    //code
    // * todo

    return dependencyGraph;
}

const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::processData(const data_id& dataId, const file_id& fileId, const IPayload* payload) const
{
    auto binaryFile = m_fileManager->binaryFile(fileId);
    auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    for(const auto& section : payload->data())
    {
        for(const auto& sectionData : section.data)
        {
            const auto nasmData = CNasmData { section.sectionName, sectionData };
            const auto dataId = nasmData.dataId(payload->id());
            const auto dependencies = nasmData.dependencies();

            const auto modificationId = CUuid { dataId };

            if (binaryFile->hasModification(modificationId)) {
                continue;
            }

            if (dependencies.size() == 0) {
                return std::make_shared<bytes::CAddBytesCommand>(
                    fileId,
                    modificationId,
                    section.sectionName,
                    nasmData.produceDataBytes(fileFormat->endianness(), fileFormat->architecture()),
                    false,
                    true,
                    false
                );
            }

            auto nasmDataUpdated = nasmData;
            auto requiredModificationIds = std::vector<CUuid> { };
            for(const auto& dependency : dependencies) {
                const auto dependencyModificationId = CUuid { dependency };
                const auto& dependencyModification = binaryFile->modification(dependencyModificationId);

                if (dependencyModification == nullptr) {
                    throw RuntimeException(std::format(strenc("Required dependency {} must be loaded before data: {}"), dependency, dataId));
                }

                nasmDataUpdated = nasmDataUpdated.resolveDependency(dependency, dependencyModification->firstAddByteAddress());

                requiredModificationIds.push_back(dependencyModificationId);
            }

            return std::make_shared<bytes::CAddBytesCommand>(
                fileId,
                modificationId,
                section.sectionName,
                nasmDataUpdated.produceDataBytes(fileFormat->endianness(), fileFormat->architecture()),
                false,
                true,
                false,
                requiredModificationIds
            );
        }
    }

    return nullptr;
}

const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::processProcedure(
    const procedure_id& procedureId,
    const file_id& fileId,
    const IPayload* payload
) const {
    return nullptr;
}

const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::processPayloadChunks(
    const std::vector<std::string>& payloadChunksOrder,
    const file_id& fileId,
    const IPayload* payload
) const {
    auto binaryFile = m_fileManager->binaryFile(fileId);
    auto fileFormat = m_fileManager->binaryFileModifiedBinaryAsFormat(fileId);

    for(const auto& chunkId : payloadChunksOrder)
    {
        const auto& dataCmd = processData(chunkId, fileId, payload);
        if (dataCmd != nullptr) {
            return dataCmd;
        }

        const auto procedureCmd = processProcedure(chunkId, fileId, payload);
        if (procedureCmd != nullptr) {
            return procedureCmd;
        }
    }

    return nullptr;
}

CNasmPayloadProcessor::CNasmPayloadProcessor(CBinaryFileStateManager* fileManager): m_fileManager(fileManager) { assert(fileManager != nullptr); }

const std::shared_ptr<IModificationCommand> CNasmPayloadProcessor::next(const file_id& fileId, const IPayload* payload) const
{
    if (payload == nullptr) {
        throw RuntimeException(strenc("An actual payload must be provided"));
    }

    auto binaryFile = m_fileManager->binaryFile(fileId);

    if (binaryFile->format() != payload->format()) {
        throw RuntimeException(strenc("Payload and Binary format mismatch!"));
    }

    if (binaryFile->arch() != payload->architecture()) {
        throw RuntimeException(strenc("Payload and Binary architecture mismatch!"));
    }

    const auto importCmd = processImports(fileId, payload);
    if (importCmd != nullptr) {
        return importCmd;
    }

    const auto dependencyGraph = buildDependencyGraph(fileId, payload);

    return processPayloadChunks(
        dependencyGraph.topologicalSort(),
        fileId,
        payload
    );
}
