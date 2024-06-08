#ifndef SRC_CORE_FILE__I_FILE_READER_HPP_
#define SRC_CORE_FILE__I_FILE_READER_HPP_




#include <string>
#include "../Binary.hpp"

class IFileReader
{
public:
	virtual ~IFileReader() {};
	virtual const CBinary read(const std::string& filePath) = 0;
};



#endif // SRC_CORE_FILE__I_FILE_READER_HPP_
