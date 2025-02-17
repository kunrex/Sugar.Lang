#include "enum.h"

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton) : DataType(skeleton->Name()->Value(), describer), UserDefinedType(skeleton)
    { }

    int Enum::SlotCount() const { return 1; }
}
