#include "array.h"

#include <map>

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Wrappers
{
    Array::Array(const DataType* arrayType) : Class("Array", Describer::Public), SingletonCollection(), arrayType(arrayType), genericSignature()
    { }

    const Array* Array::Instance(const DataType* dataType)
    {
        static std::map<string, const Array*> map;

        if (map.contains(dataType->FullName()))
            return map[dataType->FullName()];

        const auto array = new Array(dataType);
        map[dataType->FullName()] = array;
        return array;
    }

    void Array::InitialiseMembers()
    {

    }

    const std::string& Array::GenericSignature() const
    {
        if (genericSignature.empty())
            genericSignature = std::format("`1<{}>", arrayType->FullName());

        return genericSignature;
    }
}
