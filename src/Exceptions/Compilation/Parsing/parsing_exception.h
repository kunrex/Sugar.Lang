#ifndef PARSING_EXCEPTION_H
#define PARSING_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class ParsingException : public LogException
    {
        public:
            ParsingException(const std::string& message, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
