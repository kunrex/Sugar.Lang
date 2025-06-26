#ifndef INVALID_STATEMENT_EXCEPTION_H
#define INVALID_STATEMENT_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class InvalidStatementException final : public BindingException
    {
        public:
            InvalidStatementException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
