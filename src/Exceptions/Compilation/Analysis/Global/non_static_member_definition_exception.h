#ifndef NON_STATIC_MEMBER_DEFINITION_EXCEPTION_H
#define NON_STATIC_MEMBER_DEFINITION_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class NonStaticMemberDefinitionException final : public LogException
    {
        public:
            NonStaticMemberDefinitionException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
