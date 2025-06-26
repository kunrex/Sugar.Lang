#ifndef READ_WRITE_EXCEPTION_H
#define READ_WRITE_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class ReadException final : public BindingException
    {
        public:
            ReadException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };

    class WriteException final : public BindingException
    {
        public:
            WriteException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
