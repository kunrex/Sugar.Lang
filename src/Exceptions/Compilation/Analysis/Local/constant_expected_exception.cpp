#include "constant_expected_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    ConstantNotFoundException::ConstantNotFoundException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Expected constant value", parseNode, dataType)
    { }
}
