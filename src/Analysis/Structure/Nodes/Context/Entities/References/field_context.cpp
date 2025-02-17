#include "field_context.h"

#include "../../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    FieldContext::FieldContext(const Characteristic* characteristic) : VariableContext(characteristic)
    {
        if (characteristic->CheckDescriber(Describer::Static))
        {
            getInstruction = std::format("ldsfld {} {}", creationType->FullName(), characteristic->FullName());
            setInstruction = std::format("stsfld {} {}", creationType->FullName(), characteristic->FullName());;
        }
        else
        {
            getInstruction = std::format("ldfld {} {}", creationType->FullName(), characteristic->FullName());
            setInstruction = std::format("stfld {} {}", creationType->FullName(), characteristic->FullName());
        }
    }

    MemberType FieldContext::MemberType() const { return MemberType::FieldContext; }

    int FieldContext::SlotCount() const { return 1; }

    bool FieldContext::Readable() const { return characteristic->Readable(); }
    bool FieldContext::Writable() const { return characteristic->Writable(); }

    std::string FieldContext::InstructionGet() const { return getInstruction; }
    std::string FieldContext::InstructionSet() const { return setInstruction; }
}
