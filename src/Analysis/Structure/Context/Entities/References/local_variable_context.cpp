#include "local_variable_context.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    LocalVariableContext::LocalVariableContext(const IVariable* variable, const int index) : ContextNode(variable->CreationType()), variable(variable), index(index)
    { }

    MemberType LocalVariableContext::MemberType() const { return MemberType::LocalVariableContext; }

    int LocalVariableContext::SlotCount() const { return creationType->SlotCount(); }


    bool LocalVariableContext::Readable() const { return variable->Readable(); }
    bool LocalVariableContext::Writable() const { return variable->Writable(); }

    uintptr_t LocalVariableContext::Metadata() const { return reinterpret_cast<uintptr_t>(variable); }
    std::string LocalVariableContext::CILData() const { return std::to_string(index); }

    void LocalVariableContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Local Variable Context: " << variable->FullName() << "; Index: " << index << std::endl;
    }
}