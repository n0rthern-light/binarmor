#ifndef CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
#define CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_

#include "BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include "IFileReader.hpp"
#include "analysis/AnalysisRunner.hpp"
#include <memory>

class CBinaryFileStateManager
{
	IMessageBus* m_eventBus;
	IFileReader* m_fileReader;

    std::map<file_id, std::shared_ptr<CBinaryFile>> m_binaryFileMap;
    std::shared_ptr<CBinaryFile> m_binaryFileCurrent;

    std::shared_ptr<CAnalysisRunner> m_analysisRunner;
public:
	CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner);
	std::shared_ptr<CBinaryFile> binaryFile(const file_id& fileId) const;
	CBinary binaryFileBinary(const file_id& fileId) const;
	void load(const std::filesystem::path& filePath);
    void setCurrent(const file_id& fileId);
	void unload(const file_id& fileId);
    std::vector<file_id> loadedFiles() const;
	void save(const std::filesystem::path& filePath);
};

#endif // CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
