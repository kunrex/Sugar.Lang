#include "local_variable_context.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    LocalVariableContext::LocalVariableContext(const Variable* variable, const int index) : IndexedContextNode(variable, index)
    { }

    MemberType LocalVariableContext::MemberType() const { return MemberType::LocalVariableContext; }

    std::string LocalVariableContext::InstructionGet() const { return "ldloc." + index; }
    std::string LocalVariableContext::InstructionSet() const { return "stloc." + index; }
}