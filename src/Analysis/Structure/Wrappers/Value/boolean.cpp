#include "boolean.h"

#include "long.h"
#include "integer.h"
#include "short.h"
#include "../Reference/string.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure::Global;

constexpr std::string cil_boolean = "[System.Runtime]System.Boolean";

namespace Analysis::Structure::Wrappers
{
    Boolean::Boolean() : Struct(cil_boolean, Enums::Describer::Public), SingletonService()
    { }

    int Boolean::SlotCount() const { return 1; }

    void Boolean::InitialiseMembers()
    {
        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        PushExplicitCast(explicitShort);

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        explicitInteger->PushParameterType(&Instance());
        PushExplicitCast(explicitInteger);

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        PushExplicitCast(explicitLong);

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Boolean::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        PushOverload(equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        PushOverload(notEquals);

        const auto logicalNot = new BuiltInOperation(SyntaxKind::Not, &Instance(), "ldc.i4.0 ceq");
        logicalNot->PushParameterType(&Instance());
        PushOverload(logicalNot);

        const auto logicalAnd = new BuiltInOperation(SyntaxKind::And, &Instance(), "and");
        logicalAnd->PushParameterType(&Instance());
        logicalAnd->PushParameterType(&Instance());
        PushOverload(logicalAnd);

        const auto logicalOr = new BuiltInOperation(SyntaxKind::Or, &Instance(), "or");
        logicalOr->PushParameterType(&Instance());
        logicalOr->PushParameterType(&Instance());
        PushOverload(logicalNot);
    }
}
