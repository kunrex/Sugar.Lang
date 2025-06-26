#include "object.h"

#include "./string.h"

#include "../Value/boolean.h"

#include "../../Global/Functions/cast_overload.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    Object::Object() : ImplicitClass("object", Describer::Public)
    { }

    Object Object::instance;

    const Object* Object::Instance() { return &instance; }

    void Object::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    TypeKind Object::Type() const { return TypeKind::Void; }

    void Object::BindGlobal()
    {
        const auto equals = new GeneratedOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new GeneratedOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
    }

    const ICharacteristic* Object::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IConstructor* Object::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Object::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IOperatorOverload* Object::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Object::~Object()
    {
        for (const auto overload : overloads)
            delete overload.second;
    }
}