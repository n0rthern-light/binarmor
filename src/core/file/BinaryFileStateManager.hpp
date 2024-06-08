#ifndef SRC_CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
#define SRC_CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_




#include "BinaryFile.hpp"
#include <shared/message/IMessageBus.hpp>
#include "IFileReader.hpp"
#include "analysis/AnalysisRunner.hpp"
#include <memory>

class CBinaryFileStateManager
{
	IMessageBus* m_eventBus;
	IFileReader* m_fileReader;

	std::shared_ptr<CBinaryFile> m_binaryFile;
    std::shared_ptr<CAnalysisRunner> m_analysisRunner;
public:
	CBinaryFileStateManager(IMessageBus* eventBus, IFileReader* fileReader, CAnalysisRunner* analysisRunner);
	std::shared_ptr<CBinaryFile> binaryFile() const;
	CBinary binaryFileBinary() const;
	void load(const std::string& filePath);
	void save(const std::string& filePath);
};



#endif // SRC_CORE_FILE__BINARY_FILE_STATE_MANAGER_HPP_
