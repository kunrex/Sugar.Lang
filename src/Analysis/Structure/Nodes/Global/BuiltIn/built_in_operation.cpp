#include "built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInOperation::BuiltInOperation(const SyntaxKind baseOperator, const DataType* creationType, const string& instruction) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType)
    {
        signature = instruction;
    }

    MemberType BuiltInOperation::MemberType() const { return MemberType::BuiltInOperation; }

    const std::string& BuiltInOperation::SignatureString() const { return signature; }
}
