#include "list.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

constexpr std::string_view list_cil = "[mscorlib]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    List::List(const DataType* listType) : Class("List", Describer::Public), SingletonCollection(), listType(listType), genericSignature()
    { }

    const List* List::Instance(const DataType* dataType)
    {
        static std::map<string, const List*> map;

        if (map.contains(dataType->FullName()))
            return map[dataType->FullName()];

        const auto list = new List(dataType);
        map[dataType->FullName()] = list;

        list->fullName = std::format("{}{}", list_cil, list->genericSignature);
        return list;
    }

    const std::string& List::GenericSignature() const
    {
        if (genericSignature.empty())
            genericSignature = std::format("`1<{}>", listType->FullName());

        return genericSignature;
    }

    void List::InitialiseMembers()
    {

    }

}
