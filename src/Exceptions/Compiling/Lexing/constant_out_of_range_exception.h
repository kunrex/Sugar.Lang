#ifndef CONSTANT_OUT_OF_RANGE_EXCEPTION_H
#define CONSTANT_OUT_OF_RANGE_EXCEPTION_H

#include "../../log_exception.h"
#include "../../../Lexing/Tokens/Enums/type_kind.h"
#include "../../../Analysis/Structure/source_file.h"

namespace Exceptions
{
    class ConstantOutOfRangeException final : public LogException
    {
        public:
            ConstantOutOfRangeException(Tokens::Enums::TypeKind type, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
