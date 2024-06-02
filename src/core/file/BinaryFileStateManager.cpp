#include "BinaryFileStateManager.hpp"
#include "../application/events/BinaryFileLoadedEvent.hpp"
#include "core/file/BinaryAttributes.hpp"
#include "core/file/BinaryFile.hpp"
#include "core/file/analysis/AnalysisRunner.hpp"
#include <memory>
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CBinaryFileStateManager::CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner) : m_eventBus(eventBus), m_fileReader(fileReader), m_analysisRunner(analysisRunner)
{
	m_binaryFile = nullptr;
}

std::shared_ptr<CBinaryFile> CBinaryFileStateManager::binaryFile() const
{
	return m_binaryFile;
}

CBinary CBinaryFileStateManager::binaryFileBinary() const
{
	return binaryFile()->binary();
}

void CBinaryFileStateManager::load(const std::string& filePath)
{
    auto binary = m_fileReader->read(filePath);
    auto binaryAttributes = BinaryAttributes_t { };

	m_analysisRunner->run(&binary, binaryAttributes);

    m_binaryFile = std::make_shared<CBinaryFile>(filePath, binary, 0, binaryAttributes);

	m_eventBus->publish(std::make_shared<CBinaryFileLoadedEvent>());
}

void CBinaryFileStateManager::save(const std::string& filePath)
{
	throw RuntimeException(strenc("Unimplemented!"));
} 
