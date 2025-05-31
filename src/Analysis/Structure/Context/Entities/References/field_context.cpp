#include "field_context.h"

#include <format>

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FieldContext::FieldContext(const ICharacteristic* const characteristic, const bool bypassWrite) : ContextNode(characteristic->CreationType()),writable(characteristic->Writable() && (characteristic->CheckDescriber(Describer::Const) && bypassWrite)), characteristic(characteristic)
    { }

    MemberType FieldContext::MemberType() const { return MemberType::FieldContext; }

    int FieldContext::SlotCount() const { return creationType->SlotCount(); }

    bool FieldContext::Readable() const { return true; }
    bool FieldContext::Writable() const { return writable; }

    uintptr_t FieldContext::Metadata() const { return reinterpret_cast<uintptr_t>(characteristic); }
    std::string FieldContext::CILData() const { return ""; }

    void FieldContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Field Context: " << characteristic->FullName() << std::endl;
    }
}
