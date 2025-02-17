#include "dictionary.h"

#include <map>
#include <tuple>
#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

constexpr std::string_view dictionary_cil = "[mscorlib]System.Collections.Generic.Dictionary";

namespace Analysis::Structure::Wrappers
{
    Dictionary::Dictionary(const DataType* keyType, const DataType* valueType) : Class("Dictionary", Describer::Public), SingletonCollection(), keyType(keyType), valueType(valueType), genericSignature()
    { }

    const Dictionary* Dictionary::Instance(const DataType* keyType, const DataType* valueType)
    {
        static std::map<std::tuple<string, string>, const Dictionary*> map;

        const auto key = std::tuple(keyType->FullName(), valueType->FullName());
        if (map.contains(key))
            return map[key];

        const auto dictionary = new Dictionary(keyType, valueType);
        map[key] = dictionary;

        dictionary->fullName = std::format("{}{}", dictionary_cil, dictionary->genericSignature);
        return dictionary;
    }

    const std::string& Dictionary::GenericSignature() const
    {
        if (genericSignature.empty())
            genericSignature = std::format("`2<{}, {}>", keyType->FullName(), valueType->FullName());

        return genericSignature;
    }

    void Dictionary::InitialiseMembers()
    {

    }
}
