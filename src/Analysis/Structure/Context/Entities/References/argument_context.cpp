#include "argument_context.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    ArgumentContext::ArgumentContext(const Characteristic* characteristic, const int index) : IndexedContextNode(characteristic, index)
    { }

    bool ArgumentContext::Readable() const { return characteristic->Readable(); }
    bool ArgumentContext::Writable() const { return characteristic->Writable() && !characteristic->CheckDescriber(Describer::Const); }

    MemberType ArgumentContext::MemberType() const { return MemberType::FunctionArgumentContext; }

    std::string ArgumentContext::InstructionGet() const { return "ldarg." + index; }
    std::string ArgumentContext::InstructionSet() const { return "starg." + index; }
}
