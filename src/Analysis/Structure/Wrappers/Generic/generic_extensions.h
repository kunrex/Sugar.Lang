#ifndef GENERIC_EXTENSIONS_H
#define GENERIC_EXTENSIONS_H

#include <string>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Structure::Wrappers
{
    constexpr int max_tuple_length = 8;
    constexpr int max_delegate_length = 16;

    std::string MapGenericSignature(const std::vector<const Core::Interfaces::IDataType*>& types);
    std::string MapGenericCallSignature(const std::vector<const Core::Interfaces::IDataType*>& types);
}

#endif
