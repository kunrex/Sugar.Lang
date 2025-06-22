#include "dictionary.h"

#include <map>
#include <format>

#include "list.h"
#include "generic_extensions.h"

#include "../Value/boolean.h"
#include "../Value/integer.h"
#include "../Reference/string.h"
#include "../Reference/object.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/cast_overload.h"

#include "../../Global/Properties/indexer.h"
#include "../../Global/Properties/property.h"
#include "../../Global/Functions/method_function.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_dictionary = "[System.Collections.Generic]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    Dictionary::Dictionary(const IDataType* const keyType, const IDataType* const valueType) : BuiltInClass(cil_dictionary, Describer::Public), SingletonService(), genericSignature(), keyType(keyType), valueType(valueType), count(nullptr), constructor(nullptr), indexer(nullptr), implicitObject(nullptr)
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
        count = new BuiltInProperty("Count", Describer::Public, Integer::Instance(), true, std::format("callvirt instance int32 class {}::get_Count()", genericSignature), false, "");

        const auto indexer = new BuiltInIndexer(valueType, true, std::format("callvirt instance !1 class {}::get_Item(!0)", genericSignature), true, std::format("callvirt instance void class {}::set_Item(!0, !1)", genericSignature));
        indexer->PushParameterType(keyType);
        this->indexer = indexer;

        const auto containsKey = new BuiltInMethod("ContainsKey", Describer::Public, Boolean::Instance(), std::format("instance bool class {}::ContainsKey(!0)", genericSignature));
        containsKey->PushParameterType(keyType);
        functions[0] = { std::hash<string>()("ContainsKey") ^ ArgumentHash(containsKey), containsKey };

        const auto keyString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/KeyCollection<!0, !1> class {}::get_Keys() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, keyType->FullName(), keyType->FullName());
        const auto keys = new BuiltInMethod("Keys", Describer::Public, List::Instance(keyType), "");
        functions[1] = { std::hash<string>()("Keys") ^ ArgumentHash(keys), keys };

        const auto valueString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/ValueCollection<!0, !1> class {}::get_Values() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, valueType->FullName(), valueType->FullName());
        const auto values = new BuiltInMethod("Values", Describer::Public, List::Instance(valueType), "");
        functions[2] = { std::hash<string>()("Values") ^ ArgumentHash(values), values };

        const auto add = new BuiltInMethod("Add", Describer::Public, List::Instance(valueType), std::format("callvirt instance void class {}::Add(!0, !1)", genericSignature));
        add->PushParameterType(keyType);
        add->PushParameterType(valueType);
        functions[3] = { ArgumentHash(add), add };

        const auto getHash = GetHash();
        functions[4] = { ArgumentHash(getHash), getHash };

        constructor = new BuiltInConstructor(this, std::format("newobj instance void class {}::.ctor()", genericSignature));

        implicitObject = ImplicitObject();

        const auto explicitString = new GeneratedCast(String::Instance(), "callvirt instance string [System.Runtime]System.Object::ToString()");
        explicitString->PushParameterType(this);
        this->explicitString = explicitString;

        const auto equals = new ImplicitOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new ImplicitOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
    }

    const ICharacteristic* Dictionary::FindCharacteristic(const std::string& name) const
    {
        if (name == count->Name())
            return count;

        return nullptr;
    }

    const IConstructor* Dictionary::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.empty())
            return constructor;

        return nullptr;
    }

    const IFunctionDefinition* Dictionary::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IIndexerDefinition* Dictionary::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != keyType)
            return nullptr;

        return indexer;
    }

    const IFunction* Dictionary::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == Object::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    const IFunction* Dictionary::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == String::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    const IOperatorOverload* Dictionary::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Dictionary::~Dictionary()
    {
        delete count;

        for (const auto function: functions)
            delete function.second;

        delete constructor;

        delete indexer;

        delete implicitObject;

        delete explicitString;

        for (const auto overload : overloads)
            delete overload.second;
    }
}
