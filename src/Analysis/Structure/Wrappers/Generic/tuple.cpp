#include "tuple.h"

#include <map>
#include <format>

#include "generic_extensions.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Properties/property.h"
#include "../../Global/Functions/constructor.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_tuple = "[System.Runtime]System.ValueTuple";

namespace Analysis::Structure::Wrappers
{
    Tuple::Tuple() : ImplicitValueType(cil_tuple, Describer::Public), SingletonService()
    { }

    const Tuple* Tuple::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Tuple*> map;

        std::cout << types.size() << std::endl;
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

    int Tuple::SlotCount() const
    {
        if (slotCount < 0)
        {
            int totalSize = 0, maxSize = 0;

            for (const auto& characteristic : characteristics)
            {
                const auto size = characteristic->CreationType()->SlotCount();
                const auto actual_size = size + (word_size - 1) & ~(word_size - 1);

                totalSize += actual_size;
                if (actual_size > maxSize)
                    maxSize = actual_size;
            }

            slotCount = std::ceil(totalSize + (maxSize - 1) & ~(maxSize - 1) / word_size);
        }

        return slotCount;
    }

    const std::string& Tuple::FullName() const { return genericSignature; }

    void Tuple::BindGlobal()
    {
        const auto constructor = new BuiltInConstructor(this, std::format("instance void {}::.ctor({})", genericSignature, MapGenericCallSignature(types)));

        int i = 0;
        for (const auto type: types)
        {
            const auto getInstruction = std::format("ldfld !{} valuetype {}::Item{}", i, genericSignature, i);

            const auto name = std::format("Element{}", ++i);
            characteristics.push_back(new BuiltInProperty(name, Describer::Public, type, true, getInstruction, false, ""));

            constructor->PushParameterType(type);
        }

        constructors[0] = { ArgumentHash(constructor), constructor };

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("instance void {}::.ctor()", genericSignature));
        constructors[1] = { ArgumentHash(defaultConstructor), defaultConstructor };

        ImplicitValueType::BindGlobal();
    }

    const ICharacteristic* Tuple::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IConstructor* Tuple::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);

        for (const auto constructor : constructors)
            if (constructor.first == hash)
                return constructor.second;

        return nullptr;
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
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto constructor: constructors)
            delete constructor.second;
    }
}
