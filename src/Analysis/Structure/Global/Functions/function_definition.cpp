#include "function_definition.h"

#include <format>

#include "../../Wrappers/Reference/void.h"

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    FunctionDefinition::FunctionDefinition(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : Function(describer, creationType), Nameable(name)
    { }

    const std::string& FunctionDefinition::Signature() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", creationType->FullName(), name, ParameterString(this));

        return signature;
    }

    VoidDefinition::VoidDefinition(const std::string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, Void::Instance())
    { }

    MethodDefinition::MethodDefinition(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : FunctionDefinition(name, describer, creationType)
    { }
}