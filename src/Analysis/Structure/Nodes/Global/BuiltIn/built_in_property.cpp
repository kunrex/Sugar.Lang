#include "built_in_property.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInProperty::BuiltInProperty(const Enums::Describer describer, const std::string& name, const Core::DataType* creationType, std::string getInstruction, std::string setInstruction) : Property(name, describer, creationType), getInstruction(std::move(getInstruction)), setInstruction(std::move(setInstruction))
    { }

    std::string BuiltInProperty::GetInstruction() const { return getInstruction; }
    std::string BuiltInProperty::SetInstruction() const { return setInstruction; }
}
