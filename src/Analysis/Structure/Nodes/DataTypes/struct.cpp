#include "struct.h"

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::DataTypes
{
    Struct::Struct(const std::string& name, const Enums::Describer describer) : DataType(name, describer)
    { }

    int Struct::SlotCount() const
    {
        int size = 0;
        for (const auto& characteristic : characteristics)
            size += characteristic.second->CreationType()->SlotCount();

        return size;
    }

    StructSource::StructSource(const Enums::Describer describer, const DataTypeNode* skeleton) : Struct(skeleton->Name()->Value(), describer), UserDefinedType(skeleton)
    { }
}
