#include "built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInOperation::BuiltInOperation(const SyntaxKind baseOperator, const DataType* const creationType, const string& instruction) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType), parameters()
    {
        fullName = instruction;
    }

    MemberType BuiltInOperation::MemberType() const { return MemberType::BuiltInOperation; }

    const string& BuiltInOperation::FullName() const { return fullName; }

    unsigned long BuiltInOperation::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInOperation::ParameterAt(const unsigned long index) const { return parameters.at(index); }
}
