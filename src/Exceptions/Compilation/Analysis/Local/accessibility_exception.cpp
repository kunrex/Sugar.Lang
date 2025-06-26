#include "accessibility_exception.h"

#include <format>

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    AccessibilityException::AccessibilityException(const std::string& member, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("Member: `{}` is not public", member), parseNode, dataType)
    { }
}
