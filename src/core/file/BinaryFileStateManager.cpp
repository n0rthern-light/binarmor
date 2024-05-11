#include "BinaryFileStateManager.hpp"
#include "BinaryFileLoaded.hpp"
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CBinaryFileStateManager::CBinaryFileStateManager(IEventBus* _eventBus, IFileReader* _fileReader) : eventBus(_eventBus), fileReader(_fileReader)
{
	binaryFile = nullptr;
}

std::shared_ptr<CBinaryFile> CBinaryFileStateManager::getBinaryFile() const
{
	return binaryFile;
}

const CBinary& CBinaryFileStateManager::getBinaryFileBinary() const
{
	return getBinaryFile()->getBinary();
}

void CBinaryFileStateManager::load(const std::string& filePath)
{
	binaryFile = std::make_shared<CBinaryFile>(filePath, fileReader->read(filePath));

	eventBus->publish(new CBinaryFileLoaded());
}

void CBinaryFileStateManager::save(const std::string& filePath)
{
	throw RuntimeException(strenc("Unimplemented!"));
} 
