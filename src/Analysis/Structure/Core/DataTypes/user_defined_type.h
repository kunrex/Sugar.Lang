#ifndef USER_DEFINED_TYPE_H
#define USER_DEFINED_TYPE_H

#include "../../../../Parsing/ParseNodes/DataTypes/data_type_node.h"

namespace Analysis::Structure::Core
{
    class UserDefinedType
    {
        protected:
            const ParseNodes::DataTypes::DataTypeNode* skeleton;

            explicit UserDefinedType(const ParseNodes::DataTypes::DataTypeNode* skeleton);

        public:
            [[nodiscard]] const ParseNodes::DataTypes::DataTypeNode* Skeleton() const;
    };
}

#endif
