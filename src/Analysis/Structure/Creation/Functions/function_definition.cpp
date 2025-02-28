#include "function_definition.h"

#include <format>

#include "../../Global/Functions/function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    FunctionDefinition::FunctionDefinition(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Nameable(name), Function(describer, creationType), signature()
    { }

    const std::string& FunctionDefinition::Signature() const
    {
        if (signature.empty() && parent != nullptr)
            signature = std::format("{} {}::{}{}", creationType->FullName(), parent->FullName(), name, ParameterString(this));

        return signature;
    }
}