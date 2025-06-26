#include "non_static_reference_exception.h"

#include <format>

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    NonStaticReferenceException::NonStaticReferenceException(const std::string& referenced, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("Trying to reference non static: `{}` from a static scope", referenced), parseNode, dataType)
    { }
}
