#ifndef RETURN_ACCESSIBILITY_EXCEPTION_H
#define RETURN_ACCESSIBILITY_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class ReturnAccessibilityException final : public BindingException
    {
        public:
            ReturnAccessibilityException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
