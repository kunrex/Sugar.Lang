#include "enum_field.h"

#include "../../Wrappers/Value/integer.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    EnumField::EnumField(const string& name, const IDataType* const returnType) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), nullptr), returnType(returnType)
    { }

    EnumField::EnumField(const string& name, const IDataType* const returnType, const ParseNodes::ParseNode* const value) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), value), returnType(returnType)
    { }

    MemberType EnumField::MemberType() const { return MemberType::EnumField; }

    bool EnumField::Readable() const { return true; }
    bool EnumField::Writable() const { return false; }

    const IDataType* EnumField::ReturnType() const { return returnType; }
}
