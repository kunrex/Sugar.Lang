#include "local_variable_context.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    LocalVariableContext::LocalVariableContext(const Characteristic* characteristic, const int index) : IndexedContextNode(characteristic, index)
    { }

    MemberType LocalVariableContext::MemberType() const { return MemberType::LocalVariableContext; }

    bool LocalVariableContext::Readable() const { return true; }
    bool LocalVariableContext::Writable() const { return false; }

    std::string LocalVariableContext::InstructionGet() const { return "ldloc." + index; }
    std::string LocalVariableContext::InstructionSet() const { return "stloc." + index; }
}