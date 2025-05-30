#include "dictionary.h"

#include <map>
#include <format>

#include "generic_extensions.h"
#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "list.h"
#include "../Value/boolean.h"
#include "../Value/integer.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_dictionary = "[System.Collections.Generic]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    Dictionary::Dictionary(const IDataType* const keyType, const IDataType* const valueType) : BuiltInClass(cil_dictionary, Describer::Public), SingletonService(), genericSignature(), keyType(keyType), valueType(valueType), count(nullptr), functions(), constructor(nullptr), indexer(nullptr)
    { }

    const Dictionary* Dictionary::Instance(const IDataType* const keyType, const IDataType* const valueType)
    {
        static std::map<unsigned long, const Dictionary*> map;

        const std::vector types({ keyType, valueType});

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto dictionary = new Dictionary(keyType, valueType);
        dictionary->genericSignature = std::format("{}`{}<{}>", cil_dictionary, types.size(), MapGenericSignature(types));

        dictionary->BindGlobal();

        map[hash] = dictionary;
        return dictionary;
    }

    TypeKind Dictionary::Type() const { return TypeKind::Dictionary; }

    const std::string& Dictionary::FullName() const { return genericSignature; }

    void Dictionary::BindGlobal()
    {
        const auto getCount = std::format("callvirt instance int32 class {}::get_Count()", genericSignature);
        count = new BuiltInProperty("Count", Describer::Public, Integer::Instance(), true, getCount, false, "");

        const auto get = std::format("callvirt instance !1 class {}::get_Item(!0)", genericSignature);
        const auto set = std::format("callvirt instance void class {}::set_Item(!0, !1)", genericSignature);
        indexer = new BuiltInIndexer(valueType, true, get, true, set);
        indexer->PushParameterType(keyType);

        const auto containsKey = new BuiltInMethod("ContainsKey", Describer::Public, Boolean::Instance(), std::format("instance bool class {}::ContainsKey(!0)", genericSignature));
        containsKey->PushParameterType(keyType);
        functions.emplace_back(std::hash<string>()("ContainsKey") ^ ArgumentHash(containsKey), containsKey);

        const auto keyString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/KeyCollection<!0, !1> class {}::get_Keys() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, keyType->FullName(), keyType->FullName());
        const auto keys = new BuiltInMethod("Keys", Describer::Public, List::Instance(keyType), "");
        functions.emplace_back(std::hash<string>()("Keys") ^ ArgumentHash(keys), keys);

        const auto valueString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/ValueCollection<!0, !1> class {}::get_Values() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, valueType->FullName(), valueType->FullName());
        const auto values = new BuiltInMethod("Values", Describer::Public, List::Instance(valueType), "");
        functions.emplace_back(std::hash<string>()("Values") ^ ArgumentHash(values), values);

        constructor = new BuiltInConstructor(this, std::format("newobj instance void class {}::.ctor()", genericSignature));
    }

    const ICharacteristic* Dictionary::FindCharacteristic(const std::string& name) const
    {
        return name == "Count" ? count : nullptr;
    }

    const IConstructor* Dictionary::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(constructor) == ArgumentHash(argumentList) ? constructor : nullptr;
    }

    const IFunctionDefinition* Dictionary::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function: functions)
            if (std::get<0>(function) == hash)
                return std::get<1>(function);

        return nullptr;
    }

    const IIndexerDefinition* Dictionary::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(indexer) == ArgumentHash(argumentList) ? indexer : nullptr;
    }

    const IFunction* Dictionary::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Dictionary::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Dictionary::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Dictionary::~Dictionary()
    {
        delete count;

        for (const auto function: functions)
            delete std::get<1>(function);

        delete constructor;

        delete indexer;
    }
}
