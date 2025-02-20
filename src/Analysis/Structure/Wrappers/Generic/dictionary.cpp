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

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

constexpr std::string cil_dictionary = "[System.Collections.Generic]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    Dictionary::Dictionary(const DataType* const keyType, const DataType* const valueType) : Class(cil_dictionary, Describer::Public), SingletonCollection(), GenericType(), keyType(keyType), valueType(valueType)
    { }

    const Dictionary* Dictionary::Instance(const DataType* const keyType, const DataType* const valueType)
    {
        static std::map<unsigned long, const Dictionary*> map;

        const std::vector types({ keyType, valueType});

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto action = new Dictionary(keyType, valueType);
        action->genericSignature = std::format("{}`{}<{}>", cil_dictionary, types.size(), MapGenericSignature(types););

        action->InitialiseMembers();

        map[hash] = action;
        return action;
    }

    const std::string& Dictionary::FullName() const { return genericSignature; }

    void Dictionary::InitialiseMembers()
    {
        const auto count = std::format("callvirt instance int32 class {}::get_Count()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Count", &Integer::Instance(), true, count, false, ""));

        const auto get = std::format("callvirt instance !1 class {}::get_Item(!0)", genericSignature);
        const auto set = std::format("callvirt instance void class {}::set_Item(!0, !1)", genericSignature);
        const auto indexer = new BuiltInIndexer(valueType, true, get, true, set);
        indexer->PushParameterType(keyType);
        PushIndexer(indexer);

        const auto containsKey = new BuiltInMethod("ContainsKey", Describer::Public, &Boolean::Instance(), std::format("instance bool class {}::ContainsKey(!0)", genericSignature));
        containsKey->PushParameterType(keyType);
        PushFunction(containsKey);

        const auto keyString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/KeyCollection<!0, !1> class {}::get_Keys() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, keyType->FullName(), keyType->FullName());
        const auto keys = new BuiltInMethod("Keys", Describer::Public, List::Instance(keyType), "");
        PushFunction(keys);

        const auto valueString = std::format("instance [System.Collections.Generic]System.Collections.Generic.Dictionary`2/ValueCollection<!0, !1> class {}::get_Values() newobj instance void class [System.Collections.Generic]System.Collections.Generic.List`1<{}>::.ctor(class [System.Collections.Generic]System.Collections.Generic.IEnumerable`1<{}>)", genericSignature, valueType->FullName(), valueType->FullName());
        const auto values = new BuiltInMethod("Keys", Describer::Public, List::Instance(valueType), "");
        PushFunction(values);

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor()", genericSignature));
        PushConstructor(constructor);
    }
}
