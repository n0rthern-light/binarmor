#include <format>
#include <gtest/gtest.h>
#include <core/application/behave.hpp>
#include <shared/application/container.hpp>
#include <core/application/container.hpp>
#include <stdexcept>
#include "../../BinaryMother.hpp"
#include "core/file/BinaryModification.hpp"
#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/ModificationCommand.hpp"
#include "core/payload/IPayload.hpp"
#include "core/shared/attributes.hpp"
#include "shared/value/Uuid.hpp"

using namespace program::core::container::payload;

class CPayloadStub : public IPayload
{
    const std::string m_id;
    const Architecture m_architecture;
    const Format m_format;
    const std::vector<ImportRequirement_t> m_imports;
    const std::vector<SectionData_t> m_data;
    const std::vector<SectionProcedures_t> m_text;

public:
    CPayloadStub(
        const std::string& id,
        Architecture architecture,
        Format format,
        const std::vector<ImportRequirement_t>& imports,
        const std::vector<SectionData_t>& data,
        const std::vector<SectionProcedures_t>& text
    ): m_id(id), m_architecture(architecture), m_format(format), m_imports(imports), m_data(data), m_text(text) { }
    std::string id() const { return m_id; }
    Architecture architecture() const { return m_architecture; }
    Format format() const { return m_format; }
    std::vector<ImportRequirement_t> imports() const { return m_imports; }
    std::vector<SectionData_t> data() const { return m_data; }
    std::vector<SectionProcedures_t> text() const { return m_text; }
};

TEST(DefaultPayloadProcessorTest, BytesWillBeResolvedCorrectlyAndWithCorrectOrderInRegardOfDependencies)
{
    //given
    program::shared::container::init(0, nullptr);
    program::core::container::init(0, nullptr);
    program::core::application::behave(0, nullptr);
    program::core::container::file::binaryFileStateManager->load(BinaryMother::testBinaryPath("/windows/x86.exe"));
    const auto fileId = program::core::container::file::binaryFileStateManager->loadedFiles()[0];

    const auto payload = new CPayloadStub {
        "simple-payload",
        Architecture::X86,
        Format::Windows_PE,
        { { strenc("userenv.dll"), strenc("LoadUserProfile") } },
        { { strenc(".data"), {
            { strenc("functionRef dd function") },
            { strenc("importRef dd LoadUserProfile") },
            { strenc("DummyString db 'Hello Data', 0") },
            { strenc("DummyHex dd 0xDEADBEEF") }
        } } },
        { { strenc(".text"), {
            {
                strenc("functionWrapper"), {
                    strenc("push ebp, esp"),
                    strenc("sub esp, 8"),
                    strenc("xor eax, eax"),
                    strenc("call functionRef"),
                    strenc("ret")
                }
            },
            {
                strenc("function"), {
                    strenc("push ebp, esp"),
                    strenc("sub esp, 12"),
                    strenc("xor eax, eax"),
                    strenc("call LoadUserProfile"),
                    strenc("xor eax, eax"),
                    strenc("call importRef"),
                    strenc("ret")
                }
            }
        } } }
    };

    //when
    std::vector<std::shared_ptr<IModificationCommand>> commands { };
    while (const auto& command = payloadProcessor->next(fileId, payload)) {
        if (!commands.empty() && commands.back()->modificationId() == command->modificationId()) {
            throw std::runtime_error(std::format("Modification {} already registered!", command->modificationId().toString()));
        }

        commands.push_back(command);
    };

    ASSERT_EQ(commands.size(), 7);
    ASSERT_EQ(commands[0]->modificationId(), CUuid { "import:userenv.dll:LoadUserProfile" });
    ASSERT_EQ(commands[0]->type(), BinaryModificationType::WRITE_IMPORT);
    ASSERT_EQ(commands[1]->modificationId(), CUuid { "data:.data:simple-payload:DummyString" });
    ASSERT_EQ(commands[1]->type(), BinaryModificationType::WRITE_DATA);
    ASSERT_EQ(commands[2]->modificationId(), CUuid { "data:.data:simple-payload:DummyHex" });
    ASSERT_EQ(commands[2]->type(), BinaryModificationType::WRITE_DATA);
    ASSERT_EQ(commands[3]->modificationId(), CUuid { "data:.data:simple-payload:importRef" });
    ASSERT_EQ(commands[3]->type(), BinaryModificationType::WRITE_DATA);
    ASSERT_EQ(commands[4]->modificationId(), CUuid { "text:.text:simple-payload:function" });
    ASSERT_EQ(commands[4]->type(), BinaryModificationType::WRITE_CODE);
    ASSERT_EQ(commands[5]->modificationId(), CUuid { "data:.data:simple-payload:functionRef" });
    ASSERT_EQ(commands[5]->type(), BinaryModificationType::WRITE_DATA);
    ASSERT_EQ(commands[6]->modificationId(), CUuid { "code:.text:simple-payload:functionWrapper" });
    ASSERT_EQ(commands[6]->type(), BinaryModificationType::WRITE_CODE);
}

