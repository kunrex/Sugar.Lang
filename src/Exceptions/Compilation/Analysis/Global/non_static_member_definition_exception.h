#ifndef NON_STATIC_MEMBER_DEFINITION_EXCEPTION_H
#define NON_STATIC_MEMBER_DEFINITION_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class NonStaticMemberDefinitionException final : public BindingException
    {
        public:
            NonStaticMemberDefinitionException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
