#include "tuple.h"

#include <format>

#include "generic_extensions.h"

#include <map>

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "../../Global/BuiltIn/built_in_property.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_tuple = "[System.Runtime]System.ValueTuple";

namespace Analysis::Structure::Wrappers
{
    Tuple::Tuple() : BuiltInValueType(cil_tuple, Describer::Public), SingletonService(), genericSignature(), types(), constructor(nullptr)
    { }

    const Tuple* Tuple::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Tuple*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto tuple = new Tuple();
        for (const auto type : types)
            tuple->types.push_back(type);

        tuple->genericSignature = std::format("{}`{}<{}>", cil_tuple, types.size(), MapGenericSignature(types));
        tuple->BindGlobal();

        map[hash] = tuple;
        return tuple;
    }

    TypeKind Tuple::Type() const { return TypeKind::Tuple; }

    const std::string& Tuple::FullName() const { return genericSignature; }

    void Tuple::BindGlobal()
    {
        constructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor({})", genericSignature, MapGenericCallSignature(types)));

        int i = 1;
        for (const auto type: types)
        {
            const auto getInstruction = std::format("call instance {} class {}::get_Item{}()", type->FullName(), genericSignature, i);

            const auto name = std::format("Element{}", i++);
            characteristics.push_back(new BuiltInProperty(name, Describer::Public, type, true, getInstruction, false, ""));

            constructor->PushParameterType(type);
        }
    }

    const ICharacteristic* Tuple::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Tuple::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IConstructor* Tuple::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(constructor) == ArgumentHash(argumentList) ? constructor : nullptr;
    }

    const IIndexerDefinition* Tuple::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Tuple::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Tuple::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Tuple::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Tuple::~Tuple()
    {
        delete constructor;
    }
}
