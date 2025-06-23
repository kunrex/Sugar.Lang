#include "cast_overload.h"

#include <format>

#include "../../../../Exceptions/Compilation/Analysis/Local/return_value_exception.h"
#include "../../../Creation/Binding/binder_extensions.h"

#include "../../Core/DataTypes/data_type.h"
#include "../../Compilation/compilation_result.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Services;

using namespace Exceptions;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    DefinedCast::DefinedCast(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(name), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType DefinedCast::MemberType() const { return MemberType::CastOverload; }

    const string& DefinedCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->MemberType() == MemberType::Class ? "class" : "valuetype", creationType->FullName(), parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void DefinedCast::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            PushException(new ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void DefinedCast::Transpile(StringBuilder& builder) const
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

    ImplicitCast::ImplicitCast(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : DefinedCast("implicit__" + creationType->Name(), describer, creationType, body)
    { }

    ExplicitCast::ExplicitCast(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : DefinedCast("explicit__" + creationType->Name(), describer, creationType, body)
    { }

    GeneratedCast::GeneratedCast(const IDataType* const creationType, const string& instruction) : CastDefinition(Describer::PublicStatic, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType GeneratedCast::MemberType() const { return MemberType::GeneratedCast; }

    const string& GeneratedCast::FullName() const { return fullName; }

    void GeneratedCast::BindLocal()
    { }

    void GeneratedCast::Transpile(StringBuilder& builder) const
    { }

    BuiltInCast::BuiltInCast(const IDataType* const creationType, const string& instruction, const CastFunction castDelegate) : GeneratedCast(creationType, instruction), castDelegate(castDelegate)
    { }

    const string& BuiltInCast::FullName() const { return fullName; }

    CompilationResult BuiltInCast::StaticCompile(const CompilationResult& argument) const { return castDelegate(argument); }
}
