#ifndef NON_STATIC_REFERENCE_EXCEPTION_H
#define NON_STATIC_REFERENCE_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class NonStaticReferenceException final : public BindingException
    {
        public:
            NonStaticReferenceException(const std::string& referenced, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
