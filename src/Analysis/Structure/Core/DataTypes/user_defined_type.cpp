#include "user_defined_type.h"

using namespace ParseNodes::DataTypes;

namespace Analysis::Structure::Core
{
    UserDefinedType::UserDefinedType(const DataTypeNode* const skeleton) : skeleton(skeleton)
    { }

    const DataTypeNode* UserDefinedType::Skeleton() const { return skeleton; }
}
