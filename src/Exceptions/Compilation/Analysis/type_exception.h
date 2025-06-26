#ifndef TYPE_EXCEPTION_H
#define TYPE_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class TypeNotFoundException final : public LogException
    {
        public:
            TypeNotFoundException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::SourceFile* source);
    };
}

#endif
