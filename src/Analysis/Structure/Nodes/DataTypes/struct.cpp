#include "struct.h"

namespace Analysis::Structure::DataTypes
{
    Struct::Struct(const std::string& name, const Enums::Describer describer, const ParseNodes::DataTypes::StructNode* skeleton) : ITypeWrapper(name, describer, skeleton), preStack(0), characteristics()
    { }

    int Struct::SlotCount() const
    {
        int size = preStack;
        for (const auto& characteristic : characteristics)
            size += characteristic.second.CreationType()->StackSlotSize();

        return size;
    }
}
