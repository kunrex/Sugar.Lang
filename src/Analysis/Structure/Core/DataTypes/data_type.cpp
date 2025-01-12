#include "data_type.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    DataType::DataType(const std::string& name, const Enums::Describer describer) : Child(), Nameable(name), Describable(describer)
    { }

    /*void DataType::SetParent(const SourceFile* parent)
    {
        Child::SetParent(parent);
        fullName = parent->FullName() + "." + name;
    }*/
}
