#include "read_write_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    ReadException::ReadException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Cannot read this value", parseNode, dataType)
    { }

    WriteException::WriteException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Cannot write to this value", parseNode, dataType)
    { }
}
