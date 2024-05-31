#pragma once
#include "BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include "IFileReader.hpp"
#include <memory>

class CBinaryFileStateManager
{
	IMessageBus* _eventBus;
	IFileReader* _fileReader;

	std::shared_ptr<CBinaryFile> _binaryFile;
public:
	CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader);
	std::shared_ptr<CBinaryFile> binaryFile() const;
	CBinary binaryFileBinary() const;
	void load(const std::string& filePath);
	void save(const std::string& filePath);
};
