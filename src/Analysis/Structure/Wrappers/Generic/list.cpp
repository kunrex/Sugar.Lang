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

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_list = "[System.Collections.Generic]System.Collections.Generic.List";

namespace Analysis::Structure::Wrappers
{
    List::List(const IDataType* const listType) : BuiltInClass(cil_list, Describer::Public), SingletonService(), genericSignature(), listType(listType), characteristics(), functions(), constructors(), indexer(nullptr)
    { }

    const List* List::Instance(const IDataType* const dataType)
    {
        static std::map<uintptr_t, const List*> map;

        const auto hash = reinterpret_cast<uintptr_t>(dataType);

        if (map.contains(hash))
            return map.at(hash);

        const auto list = new List(dataType);
        list->genericSignature = std::format("{}`1<{}>", cil_list, dataType->FullName());

        list->BindGlobal();

        map[hash] = list;
        return list;
    }

    TypeKind List::Type() const { return TypeKind::List; }

    const std::string& List::FullName() const {  return genericSignature; }

    const IDataType* List::GenericType() const { return listType; }

    void List::BindGlobal()
    {
        const auto count = std::format("callvirt instance int32 class {}::get_Count()", genericSignature);
        characteristics.push_back(new BuiltInProperty("Count", Describer::Public, Integer::Instance(), true, count, false, ""));

        const auto capacity = std::format("callvirt instance int32 class {}::get_Capacity()", genericSignature);
        characteristics.push_back(new BuiltInProperty("Capacity", Describer::Public, Integer::Instance(), true, capacity, false, ""));

        const auto get = std::format("callvirt instance !0 class {}::get_Item(int32)", genericSignature);
        const auto set = std::format("callvirt instance void class {}::set_Item(int32, !0)", genericSignature);
        indexer = new BuiltInIndexer(listType, true, get, true, set);
        indexer->PushParameterType(Integer::Instance());

        const auto add = new BuiltInVoid("Add", Describer::Public, std::format("instance void class {}::Add(!0)", genericSignature));
        add->PushParameterType(listType);
        functions.emplace_back(std::hash<string>()("Add") ^ ArgumentHash(add), add);

        const auto clear = new BuiltInVoid("Clear", Describer::Public, std::format("instance void class {}::Clear()", genericSignature));
        functions.emplace_back(std::hash<string>()("Clear") ^ ArgumentHash(clear), clear);

        const auto contains = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), std::format("instance bool class {}::Contains(!0)", genericSignature));
        contains->PushParameterType(listType);
        functions.emplace_back(std::hash<string>()("Contains") ^ ArgumentHash(contains), contains);

        const auto remove = new BuiltInMethod("Remove", Describer::Public, Boolean::Instance(), std::format("instance bool class {}::Remove(!0)", genericSignature));
        remove->PushParameterType(listType);
        functions.emplace_back(std::hash<string>()("Remove") ^ ArgumentHash(remove), remove);

        const auto reverse = new BuiltInVoid("Reverse", Describer::Public, std::format("instance void class {}::Reverse()", genericSignature));
        functions.emplace_back(std::hash<string>()("Reverse") ^ ArgumentHash(reverse), reverse);

        const auto reverseBound = new BuiltInVoid("Reverse", Describer::Public, std::format("instance void class {}::Reverse(int32, int32)", genericSignature));
        reverseBound->PushParameterType(Integer::Instance());
        reverseBound->PushParameterType(Integer::Instance());
        functions.emplace_back(std::hash<string>()("Reverse") ^ ArgumentHash(reverseBound), reverseBound);

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor()", genericSignature));
        constructors.emplace_back(ArgumentHash(defaultConstructor), defaultConstructor);

        const auto constructor = new BuiltInConstructor(this, std::format("newobj instance void class {}::.ctor(int32)", genericSignature));
        constructor->PushParameterType(Integer::Instance());
        constructors.emplace_back(ArgumentHash(constructor), constructor);
    }

    const ICharacteristic* List::FindCharacteristic(const std::string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IConstructor* List::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);

        for (const auto constructor: constructors)
            if (std::get<0>(constructor) == hash)
                return std::get<1>(constructor);

        return nullptr;
    }

    const IFunctionDefinition* List::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function: functions)
            if (std::get<0>(function) == hash)
                return std::get<1>(function);

        return nullptr;
    }

    const IIndexerDefinition* List::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(indexer) == ArgumentHash(argumentList) ? indexer : nullptr;
    }

    const IFunction* List::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* List::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* List::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    List::~List()
    {
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete std::get<1>(function);

        for (const auto& constructor: constructors)
            delete std::get<1>(constructor);

        delete indexer;
    }
}
