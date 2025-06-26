#include "duplicate_function_definition_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    DuplicateFunctionDefinition::DuplicateFunctionDefinition(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Scopes already defines a function with the same signature.", parseNode, dataType)
    { }
}

