#include "list.h"

#include <map>
#include <format>

#include "../Value/boolean.h"
#include "../Value/integer.h"
#include "../Reference/string.h"
#include "../Reference/object.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/cast_overload.h"

#include "../../Global/Properties/indexer.h"
#include "../../Global/Properties/property.h"
#include "../../Global/Functions/void_function.h"
#include "../../Global/Functions/method_function.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_list = "[System.Collections.Generic]System.Collections.Generic.List";

namespace Analysis::Structure::Wrappers
{
    List::List(const IDataType* const listType) : BuiltInClass(cil_list, Describer::Public), SingletonService(), listType(listType), characteristics(), indexer(nullptr), implicitObject(nullptr), explicitString(nullptr)
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
        characteristics[0] = new BuiltInProperty("Count", Describer::Public, Integer::Instance(), true, std::format("callvirt instance int32 class {}::get_Count()", genericSignature), false, "");
        characteristics[1] = new BuiltInProperty("Capacity", Describer::Public, Integer::Instance(), true, std::format("callvirt instance int32 class {}::get_Capacity()", genericSignature), true, std::format("callvirt instance void class {}::set_Capacity(int32)", genericSignature));

        const auto indexer = new BuiltInIndexer(listType, true, std::format("callvirt instance !0 class {}::get_Item(int32)", genericSignature), true, std::format("callvirt instance void class {}::set_Item(int32, !0)", genericSignature));
        indexer->PushParameterType(Integer::Instance());
        this->indexer = indexer;

        const auto add = new BuiltInVoid("Add", Describer::Public, std::format("callvirt instance void {}::Add(!0)", genericSignature));
        add->PushParameterType(listType);
        functions[0] = { std::hash<string>()(add->Name()) ^ ArgumentHash(add), add };

        const auto clear = new BuiltInVoid("Clear", Describer::Public, std::format("callvirt instance void {}::Clear()", genericSignature));
        functions[1] = { std::hash<string>()(clear->Name()) ^ ArgumentHash(clear), clear };

        const auto contains = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), std::format("callvirt instance bool {}::Contains(!0)", genericSignature));
        contains->PushParameterType(listType);
        functions[2] = { std::hash<string>()(contains->Name()) ^ ArgumentHash(contains), contains };

        const auto remove = new BuiltInMethod("Remove", Describer::Public, Boolean::Instance(), std::format("callvirt instance bool {}::Remove(!0)", genericSignature));
        remove->PushParameterType(listType);
        functions[3] = { std::hash<string>()(remove->Name()) ^ ArgumentHash(remove), remove };

        const auto reverse = new BuiltInVoid("Reverse", Describer::Public, std::format("callvirt instance void {}::Reverse()", genericSignature));
        functions[4] = { std::hash<string>()(reverse->Name()) ^ ArgumentHash(reverse), reverse };

        const auto reverseBound = new BuiltInVoid("Reverse", Describer::Public, std::format("callvirt instance void {}::Reverse(int32, int32)", genericSignature));
        reverseBound->PushParameterType(Integer::Instance());
        reverseBound->PushParameterType(Integer::Instance());
        functions[5] = { std::hash<string>()(reverseBound->Name()) ^ ArgumentHash(reverseBound), reverseBound };

        const auto getHash = GetHash();
        functions[6] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("instance void {}::.ctor()", genericSignature));
        constructors[0] = { ArgumentHash(defaultConstructor), defaultConstructor };

        const auto constructor = new BuiltInConstructor(this, std::format("instance void {}::.ctor(int32)", genericSignature));
        constructor->PushParameterType(Integer::Instance());
        constructors[1] = { ArgumentHash(constructor), constructor };

        implicitObject = ImplicitObject();

        const auto explicitString = new GeneratedCast(String::Instance(), "callvirt instance string [System.Runtime]System.Object::ToString()");
        explicitString->PushParameterType(this);
        this->explicitString = explicitString;

        const auto equals = new GeneratedOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new GeneratedOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
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
            if (constructor.first == hash)
                return constructor.second;

        return nullptr;
    }

    const IFunctionDefinition* List::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IIndexerDefinition* List::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != Integer::Instance())
            return nullptr;

        return indexer;
    }

    const IFunction* List::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == Object::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    const IFunction* List::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == String::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    const IOperatorOverload* List::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    List::~List()
    {
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;

        for (const auto& constructor: constructors)
            delete constructor.second;

        delete indexer;

        delete explicitString;

        delete implicitObject;

        for (const auto overload : overloads)
            delete overload.second;
    }
}
