#include "operator_overload.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../Compilation/compilation_result.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Services;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BaseOverload::BaseOverload(const SyntaxKind baseOperator) : baseOperator(baseOperator)
    { }

    SyntaxKind BaseOverload::Operator() const { return baseOperator; }

    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const IFunction* const definition) : BaseOverload(baseOperator), definition(definition)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const IDataType* OperatorOverload::CreationType() const { return definition->CreationType(); }

    Describer OperatorOverload::Describer() const { return definition->Describer(); }

    bool OperatorOverload::ValidateDescriber(const Enums::Describer allowed) const { return definition->ValidateDescriber(allowed); }

    bool OperatorOverload::MatchDescriber(const Enums::Describer expected) const { return definition->MatchDescriber(expected); }
    bool OperatorOverload::CheckDescriber(const Enums::Describer describer) const { return definition->CheckDescriber(describer); }

    const std::string& OperatorOverload::FullName() const { return definition->FullName(); }

    unsigned long OperatorOverload::ParameterCount() const { return definition->ParameterCount(); }
    const IDataType* OperatorOverload::ParameterAt(const unsigned long index) const { return definition->ParameterAt(index); }

    GeneratedOverload::GeneratedOverload(const SyntaxKind baseOperator, const IDataType* const creationType, const std::string& instruction) : Function(Describer::PublicStatic, creationType), BaseOverload(baseOperator), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType GeneratedOverload::MemberType() const { return MemberType::GeneratedOverload; }

    BuiltInOverload::BuiltInOverload(const SyntaxKind baseOperator, const IDataType* const creationType, const std::string& instruction, const OverloadFunction overloadDelegate) : GeneratedOverload(baseOperator, creationType, instruction), overloadDelegate(overloadDelegate)
    { }

    CompilationResult BuiltInOverload::StaticCompile(const std::vector<CompilationResult>& arguments) const { return overloadDelegate(arguments); }
}
