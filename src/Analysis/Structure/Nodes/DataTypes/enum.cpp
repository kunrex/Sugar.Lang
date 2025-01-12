#include "enum.h"

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const std::string& name, const Enums::Describer describer, const ParseNodes::DataTypes::EnumNode* skeleton) : ITypeWrapper(name, describer, skeleton)
    { }

    int Enum::SlotCount() const { return 1; }
}
