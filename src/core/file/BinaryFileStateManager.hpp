#pragma once
#include "BinaryFile.hpp"
#include <shared/event/IEventBus.hpp>
#include "IFileReader.hpp"
#include <memory>

class CBinaryFileStateManager
{
	IEventBus* eventBus;
	IFileReader* fileReader;

	std::shared_ptr<CBinaryFile> binaryFile;
public:
	CBinaryFileStateManager(IEventBus* _eventBus, IFileReader* _fileReader);
	std::shared_ptr<CBinaryFile> getBinaryFile() const;
	const CBinary& getBinaryFileBinary() const;
	void load(const std::string& filePath);
	void save(const std::string& filePath);
};
