#include "accessor_body_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    AccessorBodyException::AccessorBodyException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Accessors must define a body", parseNode, dataType)
    { }
}
