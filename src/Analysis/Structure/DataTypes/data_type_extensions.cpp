#include "data_type_extensions.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    constexpr unsigned int prime = 31;
    constexpr unsigned int unique = 0x9e3779b9;

    unsigned long ArgumentHash(const IParametrized* const function)
    {
        unsigned long typeHash = 0;

        for (int i = 0; i < function->ParameterCount(); ++i)
            typeHash = (typeHash * prime) ^ std::hash<std::string>{}(function->ParameterAt(i)->FullName());

        return typeHash * unique + (typeHash << 6) + (typeHash >> 2);
    }

    unsigned long ArgumentHash(const std::vector<const IDataType*>& argumentList)
    {
        unsigned long typeHash = 0;

        for (const auto type: argumentList)
            typeHash = (typeHash * prime) ^ std::hash<std::string>{}(type->FullName());

        return typeHash * unique + (typeHash << 6) + (typeHash >> 2);
    }
}
