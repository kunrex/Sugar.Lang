#include "func.h"

#include <map>
#include <format>

#include "generic_extensions.h"

#include "../Value/boolean.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_func = "[System.Runtime]System.Func";

namespace Analysis::Structure::Wrappers
{
    Func::Func() : ImplicitClass(cil_func, Describer::Public), SingletonService()
    { }

    const Func* Func::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Func*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto func = new Func();
        for (const auto type : types)
            func->types.push_back(type);

        func->genericSignature = std::format("{}`{}<{}>", cil_func, types.size(), MapGenericSignature(types));

        func->BindGlobal();

        map[hash] = func;
        return func;
    }

    TypeKind Func::Type() const { return TypeKind::Func; }

    const std::string& Func::FullName() const { return genericSignature; }

    unsigned long Func::TypeCount() const { return types.size(); }

    const IDataType* Func::TypeAt(const unsigned long index) const { return types.at(index); }

    const std::string& Func::DelegateSignature() const { return genericSignature; }

    void Func::BindGlobal()
    {
        const auto equals = new GeneratedOverload(SyntaxKind::Equals, Boolean::Instance(), "call bool [System.Runtime]System.Delegate::op_Equality(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate)");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new GeneratedOverload(SyntaxKind::NotEquals, Boolean::Instance(), "call bool [System.Runtime]System.Delegate::op_Equality(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate) ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
    }

    const ICharacteristic* Func::FindCharacteristic(const std::string& name) const
    { return nullptr; }

    const IConstructor* Func::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Func::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IOperatorOverload* Func::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Func::~Func()
    {
        for (const auto overload : overloads)
            delete overload.second;
    }

}