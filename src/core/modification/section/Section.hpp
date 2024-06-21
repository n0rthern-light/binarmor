#pragma once

#include "SectionPermissions.hpp"
#include <shared/value/Uuid.hpp>
#include "../../file/Binaryfile.hpp"
#include "core/modification/ModificationException.hpp"
#include "shared/types/defines.hpp"
#include "shared/value/AddressType.hpp"
#include "shared/value/Unsigned.hpp"
#include <string>

using section_id = std::string;

class CSection
{
    const file_id m_fileId;
    const section_id m_id;
    const CSectionPermissions m_permissions;
    const CUnsigned m_startAddress;
    const uint_32 m_size;
    const CUnsigned m_firstFreeAddress;
    const bool m_original;

public:
    CSection(
        const file_id& fileId,
        const section_id& id,
        const CSectionPermissions& permissions,
        const CUnsigned& startAddress,
        const uint_32 size,
        const CUnsigned& firstFreeAddress,
        const bool original
    ):  m_fileId(fileId),
        m_id(id),
        m_permissions(permissions), 
        m_startAddress(startAddress),
        m_size(size),
        m_firstFreeAddress(firstFreeAddress),
        m_original(original)
    { }

    CUnsigned endAddress() const
    {
        if (m_startAddress.bitType() == AddressType::_32_BIT) {
            return CUnsigned(m_startAddress.get32() + m_size);
        } else {
            return CUnsigned(m_startAddress.get64() + m_size);
        }
    }

    CUnsigned spaceLeft() const
    {
        const auto end = endAddress();

        if (end.bitType() != m_firstFreeAddress.bitType()) {
            throw ModificationException(strenc("Start address and first free address are not the same Bit Type"));
        }

        if (end.bitType() == AddressType::_32_BIT) {
            return CUnsigned(end.get32() - m_firstFreeAddress.get32());
        } else {
            return CUnsigned(end.get64() - m_firstFreeAddress.get64());
        }
    }

    CUnsigned firstFreeAddress() const { return m_firstFreeAddress; }
};
