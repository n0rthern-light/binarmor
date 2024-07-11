#ifndef CORE_SHARED__SECTION_PERMISSIONS_HPP_
#define CORE_SHARED__SECTION_PERMISSIONS_HPP_

#include "shared/types/defines.hpp"

enum class SectionPermissionType
{
    READ = 0,
    WRITE = 1,
    EXECUTE = 2,
};

class CSectionPermissions
{
    uint_8 m_valFlags;
public:
    CSectionPermissions(SectionPermissionType permission)
    {
        m_valFlags ^= m_valFlags; // xor to clear

        m_valFlags |= static_cast<uint_8>(SectionPermissionType::READ); // every section is readable

        if (permission == SectionPermissionType::WRITE) {
            m_valFlags |= static_cast<uint_8>(SectionPermissionType::WRITE);
        }

        if (permission == SectionPermissionType::EXECUTE) {
            m_valFlags |= static_cast<uint_8>(SectionPermissionType::EXECUTE);
        }
    }

    bool hasPermissionTo(SectionPermissionType permission) {
        return (m_valFlags & static_cast<uint_8>(permission)) == static_cast<uint_8>(permission);
    }
};

#endif // CORE_SHARED__SECTION_PERMISSIONS_HPP_
