#include "func.h"

#include <map>
#include <format>

#include "generic_extensions.h"

#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_func = "[System.Runtime]System.Func";

namespace Analysis::Structure::Wrappers
{
    Func::Func() : BuiltInClass(cil_func, Describer::Public), SingletonService(), genericSignature(), types()
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

        func->InitializeMembers();

        map[hash] = func;
        return func;
    }

    TypeKind Func::Type() const { return TypeKind::Func; }

    const std::string& Func::FullName() const { return genericSignature; }

    unsigned long Func::TypeCount() const { return types.size(); }

    const IDataType* Func::TypeAt(const unsigned long index) const { return types.at(index); }

    const std::string& Func::DelegateSignature() const { return genericSignature; }

    void Func::InitializeMembers()
    { }

    const ICharacteristic* Func::FindCharacteristic(const std::string& name) const
    { return nullptr; }

    const IFunction* Func::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunctionDefinition* Func::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Func::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Func::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Func::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Func::FindOverload(const SyntaxKind base) const
    { return nullptr; }
}