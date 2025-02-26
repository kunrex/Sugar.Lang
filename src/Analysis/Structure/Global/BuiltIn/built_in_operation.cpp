#include "built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInOperation::BuiltInOperation(const SyntaxKind baseOperator, const Interfaces::IDataType* const creationType, const string& instruction) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInOperation::MemberType() const { return MemberType::BuiltInOperation; }

    const string& BuiltInOperation::FullName() const { return fullName; }
}
