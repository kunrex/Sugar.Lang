#include "function_definition.h"

#include <format>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    FunctionDefinition::FunctionDefinition(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : Nameable(name), Function(describer, creationType), signature()
    { }

    const std::string& FunctionDefinition::Signature() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", creationType->FullName(), name, ParameterString(this));

        return signature;
    }
}