#include "FixBinaryResizeHandler.hpp"
#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"

using namespace program::core::modification::resize;
using namespace program::core::file;

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
    // throw RuntimeException(strenc("Well this is not implemented"));
    // this is too complex and nearly unachievable, so rather leave the idea of fixing binary resizement (AT LEAST in the lower address space sections)
    // may be considered okay in the IAT / higher addresses
}
