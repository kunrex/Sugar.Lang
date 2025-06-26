#ifndef ACCESSOR_BODY_EXCEPTION_H
#define ACCESSOR_BODY_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class AccessorBodyException final : public BindingException
    {
        public:
            AccessorBodyException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
