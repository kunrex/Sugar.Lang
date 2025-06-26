#include "invalid_global_statement_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    InvalidGlobalStatementException::InvalidGlobalStatementException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Global scopes can contain only variable, property and function definitions.", parseNode, dataType)
    { }
}

