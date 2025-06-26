#include "invalid_statement_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    InvalidStatementException::InvalidStatementException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Only initialisation, expression and function call can be a valid statement", parseNode, dataType)
    { }
}

