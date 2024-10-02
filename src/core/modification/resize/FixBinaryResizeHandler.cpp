#include "FixBinaryResizeHandler.hpp"

CFixBinaryResizeHandler::CFixBinaryResizeHandler(CBinaryFileStateManager* fileManager):
    m_fileManager(fileManager)
{ }

/*
- Import Address Table (IAT)
- Export Table
- Relocation Table (Base Relocations)
- .text section (code)
- .data section (data references)
- Debug Information
- Exception Handling (if any)
*/

void CFixBinaryResizeHandler::handle(const CFixBinaryResizeCommand& command)
{


}
