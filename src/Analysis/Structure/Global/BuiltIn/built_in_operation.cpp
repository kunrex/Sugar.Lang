#include "built_in_operation.h"

#include "../../Compilation/compilation_result.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInOperation::BuiltInOperation(const SyntaxKind baseOperator, const IDataType* const creationType, const string& instruction, const OverloadFunction overloadDelegate) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType), BuiltInFunction(), overloadDelegate(overloadDelegate)
    {
        fullName = instruction;
    }

    MemberType BuiltInOperation::MemberType() const { return MemberType::BuiltInOperation; }

    const string& BuiltInOperation::FullName() const { return fullName; }

    CompilationResult BuiltInOperation::StaticCompile(const std::vector<CompilationResult>& arguments) const { return overloadDelegate(arguments); }

    void BuiltInOperation::Bind()
    { }
}
