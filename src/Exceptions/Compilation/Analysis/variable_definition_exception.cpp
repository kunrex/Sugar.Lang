#include "variable_definition_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    DuplicateVariableDefinitionException::DuplicateVariableDefinitionException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Scope already defines a variable with the same name", parseNode, dataType)
    { }
}
