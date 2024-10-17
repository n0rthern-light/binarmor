#ifndef CORE_SHARED__SECTION_PERMISSIONS_HPP_
#define CORE_SHARED__SECTION_PERMISSIONS_HPP_

#include "shared/types/defines.hpp"

namespace program::core::shared {
    enum class SectionPermissionType
    {
        READ = 0,
        WRITE = 1,
        EXECUTE = 2,
    };

    class CSectionPermissions
    {
        program::shared::types::uint_8 m_valFlags;
        CSectionPermissions(const program::shared::types::uint_8 valFlags): m_valFlags(valFlags) { }

    public:
        CSectionPermissions(): CSectionPermissions(0) { }
        CSectionPermissions(SectionPermissionType permission)
        {
            m_valFlags ^= m_valFlags;

            m_valFlags |= static_cast<program::shared::types::uint_8>(SectionPermissionType::READ); // every section is readable

            if (permission == SectionPermissionType::WRITE) {
                m_valFlags |= static_cast<program::shared::types::uint_8>(SectionPermissionType::WRITE);
            }

            if (permission == SectionPermissionType::EXECUTE) {
                m_valFlags |= static_cast<program::shared::types::uint_8>(SectionPermissionType::EXECUTE);
            }
        }

        bool hasPermissionTo(SectionPermissionType permission) const
        {
            return (m_valFlags & static_cast<program::shared::types::uint_8>(permission)) == static_cast<program::shared::types::uint_8>(permission);
        }

        CSectionPermissions withPermission(SectionPermissionType permission) const
        {
            auto flags = static_cast<program::shared::types::uint_8>(m_valFlags | static_cast<program::shared::types::uint_8>(permission));
            return CSectionPermissions{ flags };
        }

        bool operator==(const CSectionPermissions other) const
        {
            return other.m_valFlags == m_valFlags;
        }
    };
}

#endif // CORE_SHARED__SECTION_PERMISSIONS_HPP_
