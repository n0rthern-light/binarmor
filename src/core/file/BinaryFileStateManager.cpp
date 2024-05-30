#include "BinaryFileStateManager.hpp"
#include "events/BinaryFileLoadedEvent.hpp"
#include <shared/RuntimeException.hpp>
#include <shared/self_obfuscation/strenc.hpp>

CBinaryFileStateManager::CBinaryFileStateManager(IEventBus* eventBus, IFileReader* fileReader) : _eventBus(eventBus), _fileReader(fileReader)
{
	_binaryFile = nullptr;
}

std::shared_ptr<CBinaryFile> CBinaryFileStateManager::binaryFile() const
{
	return _binaryFile;
}

CBinary CBinaryFileStateManager::binaryFileBinary() const
{
	return binaryFile()->binary();
}

void CBinaryFileStateManager::load(const std::string& filePath)
{
	_binaryFile = std::make_shared<CBinaryFile>(filePath, _fileReader->read(filePath));

	_eventBus->publish(new CBinaryFileLoadedEvent());
}

void CBinaryFileStateManager::save(const std::string& filePath)
{
	throw RuntimeException(strenc("Unimplemented!"));
} 
