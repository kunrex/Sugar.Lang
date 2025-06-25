#include "operator_overload.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"
#include "../../Compilation/compilation_result.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

#include "../../../../Exceptions/exception_manager.h"
#include "../../../../Exceptions/Compilation/Analysis/Local/return_value_exception.h"

using namespace Services;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(std::format("operator__{}", static_cast<short>(baseOperator))), OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const std::string& OperatorOverload::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->MemberType() == MemberType::Class ? "class" : "valuetype", creationType->FullName(), parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void OperatorOverload::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            ExceptionManager::PushException(ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void OperatorOverload::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), creationType->FullName(), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    ImplicitOverload::ImplicitOverload(const SyntaxKind baseOperator, const IDataType* const creationType, const std::string& instruction) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType ImplicitOverload::MemberType() const { return MemberType::GeneratedOverload; }

    const std::string& ImplicitOverload::FullName() const { return fullName; }

    void ImplicitOverload::BindLocal()
    { }

    void ImplicitOverload::Transpile(StringBuilder& builder) const
    { }

    BuiltInOverload::BuiltInOverload(const SyntaxKind baseOperator, const IDataType* const creationType, const std::string& instruction, const OverloadFunction overloadDelegate) : ImplicitOverload(baseOperator, creationType, instruction), overloadDelegate(overloadDelegate)
    { }

    const std::string& BuiltInOverload::FullName() const { return fullName; }

    CompilationResult BuiltInOverload::StaticCompile(const std::vector<CompilationResult>& arguments) const { return overloadDelegate(arguments); }
}
