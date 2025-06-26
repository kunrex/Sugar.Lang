#ifndef OVERLOAD_NOT_FOUND_EXCEPTION_H
#define OVERLOAD_NOT_FOUND_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class OverloadNotFoundException final : public BindingException
    {
        public:
            OverloadNotFoundException(Tokens::Enums::SyntaxKind kind, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
