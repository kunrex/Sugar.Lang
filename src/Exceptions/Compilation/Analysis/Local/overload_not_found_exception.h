#ifndef OVERLOAD_NOT_FOUND_EXCEPTION_H
#define OVERLOAD_NOT_FOUND_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class OverloadNotFoundException final : public LogException
    {
        public:
            OverloadNotFoundException(Tokens::Enums::SyntaxKind kind, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
