#include "binding_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    BindingException::BindingException(const std::string& message, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : LogException(message, parseNode->Token().Index(), dataType->Parent())
    { }
}
