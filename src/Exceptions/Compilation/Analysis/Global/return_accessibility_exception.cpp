#include "return_accessibility_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    ReturnAccessibilityException::ReturnAccessibilityException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Return type is less accessible than member.", parseNode, dataType)
    { }
}
