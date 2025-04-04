#include "funcref_context.h"

#include "function_extensions.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FuncRefContext::FuncRefContext(const IDataType* const creationType, const IContextNode* const object, const IFunctionDefinition* const function) : UnaryContextNode(creationType, object), slotCount(std::max(creationType->SlotCount(), object->SlotCount())), function(function)
    { }

    MemberType FuncRefContext::MemberType() const { return MemberType::FuncRefContext; }

    int FuncRefContext::SlotCount() const { return slotCount; }

    bool FuncRefContext::Readable() const { return false; }
    bool FuncRefContext::Writable() const { return false; }

    string FuncRefContext::CILData() const
    {
        return "ldftn " + function->Signature();
    }
}
