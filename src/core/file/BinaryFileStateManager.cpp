#include "BinaryFileStateManager.hpp"
#include "../application/events/FileLoadedEvent.hpp"
#include "../application/events/FileUnloadedEvent.hpp"
#include "core/file/BinaryAttributes.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/analysis/AnalysisRunner.hpp"
#include <memory>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CBinaryFileStateManager::CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner) : m_eventBus(eventBus), m_fileReader(fileReader), m_analysisRunner(analysisRunner)
{
    m_vecBinaryFileId = { };
    m_binaryFileMap = { };
    m_binaryFileCurrent = nullptr;
}

binary_file_ptr CBinaryFileStateManager::binaryFile(const file_id& fileId) const
{
    return m_binaryFileMap.at(fileId);
}

CBinary CBinaryFileStateManager::binaryFileBinary(const file_id& fileId) const
{
    return binaryFile(fileId)->binary();
}

void CBinaryFileStateManager::load(const std::filesystem::path& filePath)
{
    auto binary = m_fileReader->read(filePath.string());
    auto binaryAttributes = BinaryAttributes_t { };

    m_analysisRunner->run(&binary, binaryAttributes);

    const auto tmpBinary = std::make_shared<CBinaryFile>(filePath, binary, 0, binaryAttributes);
    const auto fileId = tmpBinary->fileId();

    if (m_binaryFileMap.find(fileId) != m_binaryFileMap.end()) {
        throw RuntimeException(strenc("The choosen file is already loaded. Please, select another one."));
    }

    m_binaryFileMap[fileId] = std::move(tmpBinary);
    m_vecBinaryFileId.push_back(fileId);
    setCurrentWorkFile(fileId);

    m_eventBus->publish(std::make_shared<CFileLoadedEvent>(fileId));
}

void CBinaryFileStateManager::setCurrentWorkFile(const file_id& fileId)
{
    m_binaryFileCurrent = binaryFile(fileId);
}

void CBinaryFileStateManager::unload(const file_id fileId)
{
    auto res = m_binaryFileMap.find(fileId);

    if (res == m_binaryFileMap.end()) {
        throw RuntimeException(strenc("Cannot find file: ") + fileId);
    }
    m_binaryFileMap.erase(res);

    for(auto it = m_vecBinaryFileId.begin(); it != m_vecBinaryFileId.end();) {
        if (strcmp(it->c_str(), fileId.c_str()) == 0) {
            m_vecBinaryFileId.erase(it);
        } else {
            ++it;
        }
    }

    m_eventBus->publish(std::make_shared<CFileUnloadedEvent>(fileId));
}

std::vector<file_id> CBinaryFileStateManager::loadedFiles() const
{
    return m_vecBinaryFileId;
}

void CBinaryFileStateManager::save(const std::filesystem::path& filePath)
{
    throw RuntimeException(strenc("Unimplemented!"));
} 
