#ifndef DATA_TYPE_EXTENSIONS_H
#define DATA_TYPE_EXTENSIONS_H

#include "../Core/DataTypes/data_type.h"

namespace Analysis::Structure::DataTypes
{
    constexpr int word_size = 8;
    constexpr std::string_view hashCodeFunction = "GetHash";

    unsigned long ArgumentHash(const Core::Interfaces::IParametrized* function);
    unsigned long ArgumentHash(const std::vector<const Core::Interfaces::IDataType*>& argumentList);
}

#endif
