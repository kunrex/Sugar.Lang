#include "list.h"

#include <map>
#include <format>

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/BuiltIn/built_in_void.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "../Value/boolean.h"
#include "../Value/integer.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

constexpr std::string cil_list = "[System.Collections.Generic]System.Collections.Generic.List";

namespace Analysis::Structure::Wrappers
{
    List::List(const DataType* const listType) : Class(cil_list, Describer::Public), SingletonCollection(), listType(listType)
    { }

    const List* List::Instance(const DataType* const dataType)
    {
        static std::map<unsigned long, const List*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto list = new List(dataType);
        list->genericSignature = std::format("{}`1<{}>", cil_list, dataType->FullName());

        list->InitialiseMembers();

        map[hash] = list;
        return list;
    }

    const std::string& List::FullName() const {  return genericSignature; }

    void List::InitialiseMembers()
    {
        const auto count = std::format("callvirt instance int32 class {}::get_Count()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Count", &Integer::Instance(), true, count, false, ""));

        const auto capacity = std::format("callvirt instance int32 class {}::get_Capacity()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Count", &Integer::Instance(), true, capacity, false, ""));

        const auto get = std::format("callvirt instance !0 class {}::get_Item(int32)", genericSignature);
        const auto set = std::format("callvirt instance void class {}::set_Item(int32, !0)", genericSignature);
        const auto indexer = new BuiltInIndexer(listType, true, get, true, set);
        indexer->PushParameterType(&Integer::Instance());
        PushIndexer(indexer);

        const auto add = new BuiltInVoid("Add", Describer::Public, std::format("instance void class {}::Add(!0)", genericSignature));
        add->PushParameterType(listType);
        PushFunction(add);

        const auto clear = new BuiltInVoid("Clear", Describer::Public, std::format("instance void class {}::Clear()", genericSignature));
        PushFunction(clear);

        const auto contains = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance(), std::format("instance bool class {}::Contains(!0)", genericSignature));
        contains->PushParameterType(listType);
        PushFunction(clear);

        const auto remove = new BuiltInMethod("Remove", Describer::Public, &Boolean::Instance(), std::format("instance bool class {}::Remove(!0)", genericSignature));
        remove->PushParameterType(listType);
        PushFunction(remove);

        const auto reverse = new BuiltInVoid("Reverse", Describer::Public, std::format("instance void class {}::Reverse()", genericSignature));
        PushFunction(reverse);

        const auto reverseBound = new BuiltInVoid("Reverse", Describer::Public, std::format("instance void class {}::Reverse(int32, int32)", genericSignature));
        reverseBound->PushParameterType(&Integer::Instance());
        reverseBound->PushParameterType(&Integer::Instance());
        PushFunction(reverseBound);

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor()", genericSignature));
        PushConstructor(defaultConstructor);

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor(int32)", genericSignature));
        constructor->PushParameterType(&Integer::Instance());
        PushConstructor(constructor);
    }
}
