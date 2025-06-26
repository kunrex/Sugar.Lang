#ifndef ACCESSIBILITY_EXCEPTION_H
#define ACCESSIBILITY_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class AccessibilityException final : public BindingException
    {
        public:
            AccessibilityException(const std::string& member, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
