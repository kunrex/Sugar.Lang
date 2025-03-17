#ifndef FUNC_REF_EXCEPTION_H
#define FUNC_REF_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class FuncRefException final : public LogException
    {
        public:
            FuncRefException(const std::string& member, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
