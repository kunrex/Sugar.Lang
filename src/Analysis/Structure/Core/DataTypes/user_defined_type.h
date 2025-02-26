#ifndef USER_DEFINED_TYPE_H
#define USER_DEFINED_TYPE_H

#include "../Interfaces/Creation/i_characteristic.h"

#include "../../../../Parsing/ParseNodes/DataTypes/data_type_node.h"

namespace Analysis::Structure::Core
{
    class UserDefinedType
    {
        protected:
            const ParseNodes::DataTypes::DataTypeNode* skeleton;

            explicit UserDefinedType(const ParseNodes::DataTypes::DataTypeNode* skeleton);

        public:

            [[nodiscard]] virtual std::vector<const Interfaces::ICharacteristic*> AllCharacteristics() const = 0;

            [[nodiscard]] const ParseNodes::DataTypes::DataTypeNode* Skeleton() const;

            virtual ~UserDefinedType() = default;
    };
}

#endif
