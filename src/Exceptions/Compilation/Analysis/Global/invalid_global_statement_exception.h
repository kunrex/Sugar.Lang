#ifndef INVALID_GLOBAL_STATEMENT_EXCEPTION_H
#define INVALID_GLOBAL_STATEMENT_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class InvalidGlobalStatementException final : public BindingException
    {
        public:
            InvalidGlobalStatementException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
