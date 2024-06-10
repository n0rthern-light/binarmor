#include "BinaryFileStateManager.hpp"
#include "../application/events/FileLoadedEvent.hpp"
#include "../application/events/FileUnloadedEvent.hpp"
#include "core/file/BinaryAttributes.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/file/analysis/AnalysisRunner.hpp"
#include <memory>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CBinaryFileStateManager::CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner) : m_eventBus(eventBus), m_fileReader(fileReader), m_analysisRunner(analysisRunner)
{
	m_binaryFileMap = { };
	m_binaryFileCurrent = nullptr;
}

std::shared_ptr<CBinaryFile> CBinaryFileStateManager::binaryFile(const file_id& fileId) const
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

    const auto fileId = filePath.string();
    m_binaryFileMap[fileId] = std::make_shared<CBinaryFile>(filePath, binary, 0, binaryAttributes);
    setCurrent(fileId);

	m_eventBus->publish(std::make_shared<CFileLoadedEvent>(fileId));
}

void CBinaryFileStateManager::setCurrent(const file_id& fileId)
{
    m_binaryFileCurrent = binaryFile(fileId);
}

void CBinaryFileStateManager::unload(const file_id& fileId)
{
    auto it = m_binaryFileMap.find(fileId);
    if (it == m_binaryFileMap.end()) {
        return;
    }

    m_binaryFileMap.erase(it);

	m_eventBus->publish(std::make_shared<CFileUnloadedEvent>(fileId));
}

std::vector<file_id> CBinaryFileStateManager::loadedFiles() const
{
    auto vec = std::vector<file_id> { };
    for(const auto& pair : m_binaryFileMap) {
        vec.push_back(pair.first);
    }

    return vec;
}

void CBinaryFileStateManager::save(const std::filesystem::path& filePath)
{
	throw RuntimeException(strenc("Unimplemented!"));
} 
