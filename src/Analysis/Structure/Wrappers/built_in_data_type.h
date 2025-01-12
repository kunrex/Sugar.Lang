#ifndef BUILT_IN_DATA_TYPE_H
#define BUILT_IN_DATA_TYPE_H

#include <string>

#include "../Core/DataTypes/data_type.h"

namespace Analysis::Structure::Wrappers
{
    class BuiltInDataType : public Core::DataType
    {
        public:
            BuiltInDataType(std::string name);

    };
}

#endif
