#include "built_in_function.h"

namespace Analysis::Structure::Global
{
    BuiltInFunction::BuiltInFunction(const Enums::Describer describer, const std::string& name, const Core::DataType* creationType, const std::string& instruction) : FunctionDefinition(name, describer, creationType), BuiltInInstruction(instruction)
    { }
}
