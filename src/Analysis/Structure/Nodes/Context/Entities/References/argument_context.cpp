#include "argument_context.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    ArgumentContext::ArgumentContext(const Variable* variable, const int index) : IndexedContextNode(variable, index)
    { }

    MemberType ArgumentContext::MemberType() const { return MemberType::FunctionArgumentContext; }

    std::string ArgumentContext::InstructionGet() const { return "ldarg." + index; }
    std::string ArgumentContext::InstructionSet() const { return "starg." + index; }
}
