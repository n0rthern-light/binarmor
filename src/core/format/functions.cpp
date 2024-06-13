#include "functions.hpp"
#include <shared/self_obfuscation/strenc.hpp>
#include <shared/RuntimeException.hpp>

void format::assertBinaryNotNull(const CBinary* binary)
{
    if (!binary) {
        throw RuntimeException(strenc("Binary is not present"));
    }
}

