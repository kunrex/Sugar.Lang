#include "return.h"

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Return::Return() : ContextNode(&Object::Instance())
    { }

    Return::Return(const DataType* const dataType) : ContextNode(dataType)
    { }

    MemberType Return::MemberType() const { return MemberType::Return; }

    bool Return::Readable() const { return false; }
    bool Return::Writable() const { return false; }

    std::string Return::InstructionGet() const { return "ret"; }
    std::string Return::InstructionSet() const { return ""; }
}
