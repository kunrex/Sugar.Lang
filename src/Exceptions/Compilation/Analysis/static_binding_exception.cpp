#include "static_binding_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    StaticBindingException::StaticBindingException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Static structures can only define static members", parseNode, dataType)
    { }
}