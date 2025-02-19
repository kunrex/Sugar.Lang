#ifndef DATA_TYPE_EXTENSIONS_H
#define DATA_TYPE_EXTENSIONS_H

#include "../Core/DataTypes/data_type.h"

namespace Analysis::Structure::DataTypes
{
    constexpr int word_size = 8;

    unsigned long ArgumentHash(const Core::Interfaces::IFunction* function);
    unsigned long ArgumentHash(const std::vector<const Core::DataType*>& argumentList);
}

#endif
