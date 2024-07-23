#ifndef CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
#define CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_

#include "BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include "IFileReader.hpp"
#include "../analysis/AnalysisRunner.hpp"
#include <memory>

class CBinaryFileStateManager
{
    IMessageBus* m_eventBus;
    IFileReader* m_fileReader;

    std::vector<file_id> m_vecBinaryFileId;
    std::map<file_id, binary_file_ptr> m_binaryFileMap;
    binary_file_ptr m_binaryFileCurrent;

    CAnalysisRunner* m_analysisRunner;
public:
    CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner);
    binary_file_ptr binaryFile(const file_id& fileId) const;
    CBinary binaryFileModifiedBinary(const file_id& fileId) const;
    void load(const std::filesystem::path& filePath);
    void setCurrentWorkFile(const file_id& fileId);
    void unload(const file_id fileId);
    std::vector<file_id> loadedFiles() const;
    void save(const std::filesystem::path& filePath);
};

#endif // CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
