#include "dictionary.h"

#include <map>
#include <tuple>
#include <format>

#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_indexer.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "../Value/boolean.h"
#include "../Value/integer.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_dictionary = "[System.Collections.Generic]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    Dictionary::Dictionary(const DataType* keyType, const DataType* valueType) : Class(cil_dictionary, Describer::Public), SingletonCollection(), keyType(keyType), valueType(valueType), genericSignature()
    { }

    const Dictionary* Dictionary::Instance(const DataType* keyType, const DataType* valueType)
    {
        static std::map<std::tuple<string, string>, const Dictionary*> map;

        const auto key = std::tuple(keyType->FullName(), valueType->FullName());
        if (map.contains(key))
            return map[key];

        const auto dictionary = new Dictionary(keyType, valueType);
        map[key] = dictionary;

        dictionary->genericSignature = std::format("`2<{}, {}>", keyType->FullName(), valueType->FullName());
        dictionary->fullName = std::format("{}{}", cil_dictionary, dictionary->genericSignature);
        return dictionary;
    }

    const std::string& Dictionary::GenericSignature() const
    {
        return genericSignature;
    }

    void Dictionary::InitialiseMembers()
    {
        const auto count = std::format("callvirt instance int32 [System.Collections.Generic]System.Collections.Generic.Dictionary{}::get_Count()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Count", &Integer::Instance(), true, count, false, ""));

        const auto get = std::format("callvirt instance !1 [System.Collections.Generic]System.Collections.Generic.Dictionary{}::get_Item(!0)", genericSignature);
        const auto set = std::format("callvirt instance void [System.Collections.Generic]System.Collections.Generic.Dictionary{}::set_Item(!0, !1)", genericSignature);
        PushIndexer(new BuiltInIndexer(valueType, true, get, true, set));

        const auto containsKey = new BuiltInGenericMethod("call instance bool [System.Collections.Generic]System.Collections.Generic.Dictionary`2<!0, !1>::ContainsKey(!0)", Describer::Public, &Boolean::Instance());
        containsKey->PushParameterType(keyType);
        PushFunction(containsKey);
    }
}
