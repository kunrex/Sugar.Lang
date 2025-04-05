#include "local_variable_context.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    LocalVariableContext::LocalVariableContext(const IVariable* variable, const int index) : IndexedContext(variable, index)
    { }

    MemberType LocalVariableContext::MemberType() const { return MemberType::LocalVariableContext; }

    int LocalVariableContext::SlotCount() const { return creationType->SlotCount(); }

    std::string LocalVariableContext::CILData() const { return std::to_string(index); }

}