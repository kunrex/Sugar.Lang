#include "object.h"

#include "./string.h"
#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_object = "[System.Runtime]System.Object";

namespace Analysis::Structure::Wrappers
{
    Object::Object() : BuiltInClass(cil_object, Describer::Public), toString(nullptr)
    {
        BindGlobal();
    }

    TypeKind Object::Type() const { return TypeKind::Void; }

    const Object* Object::Instance()
    {
        static const Object instance;
        return &instance;
    }

    void Object::BindGlobal()
    {
        toString = new BuiltInCast(String::Instance(), "callvirt instance string class [System.Runtime]System.Object::ToString()", nullptr);
        toString->PushParameterType(this);
    }

    const ICharacteristic* Object::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Object::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IConstructor* Object::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Object::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Object::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Object::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (ArgumentHash( { toString->CreationType(), toString->ParameterAt(0) }) == ArgumentHash({ returnType, fromType }))
            return toString;

        return nullptr;
    }

    const IOperatorOverload* Object::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Object::~Object()
    {
        delete toString;
    }
}