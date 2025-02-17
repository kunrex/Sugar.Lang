#include "user_defined_type.h"

namespace Analysis::Structure::Core
{
    UserDefinedType::UserDefinedType(const ParseNodes::DataTypes::DataTypeNode* skeleton) : skeleton(skeleton)
    { }

    const ParseNodes::DataTypes::DataTypeNode* UserDefinedType::Skeleton() const { return skeleton; }
}
