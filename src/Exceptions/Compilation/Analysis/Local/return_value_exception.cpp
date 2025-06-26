#include "return_value_exception.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    ReturnValueException::ReturnValueException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Not all paths return a value", parseNode, dataType)
    { }
}
