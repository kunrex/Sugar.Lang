#include "array.h"

#include <map>

#include <format>

#include "../../Global/BuiltIn/built_in_property.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/BuiltIn/built_in_constructor.h"
#include "../../Global/BuiltIn/built_in_indexer.h"

#include "../Value/integer.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

namespace Analysis::Structure::Wrappers
{
    Array::Array(const DataType* const arrayType) : Class(std::format("{} {}[]", arrayType->MemberType() == MemberType::Class ? "class" : "valuetype", arrayType->FullName()), Describer::Public), SingletonCollection(), arrayType(arrayType)
    { }

    const Array* Array::Instance(const DataType* const dataType)
    {
        static std::map<unsigned long, const Array*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto array = new Array(dataType);
        array->genericSignature = std::format("{} {}[]", dataType->MemberType() == MemberType::Class ? "class" : "valuetype", dataType->FullName());

        array->InitialiseMembers();

        map[hash] = array;
        return array;
    }

    const std::string& Array::FullName() const { return genericSignature; }

    void Array::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Length", &Integer::Instance(), true, "ldlen", false, ""));

        const auto constructor = new BuiltInConstructor(this, std::format("newarr {}", arrayType->FullName()));
        constructor->PushParameterType(&Integer::Instance());
        PushConstructor(constructor);

        if (arrayType->MemberType() == MemberType::Class)
        {
            const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.ref", true, "stelem.ref");
            indexer->PushParameterType(&Integer::Instance());
            PushIndexer(indexer);
        }
        else
        {
            const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem", true, "stelem");
            indexer->PushParameterType(&Integer::Instance());
            PushIndexer(indexer);
        }
    }
}
