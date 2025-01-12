#ifndef LEXER_H
#define LEXER_H

#include "../../Services/singleton_service.h"

#include "../../Analysis/Structure/source_file.h"

namespace Lexing
{
    class Lexer final : public Services::SingletonService<Lexer>
    {
        private:
            unsigned long index;
            Analysis::Structure::SourceFile* source;

            [[nodiscard]] char LookAhead() const;

            void ReadString();
            void ReadNumber();
            void ReadKeyword();
            void ReadCharacter();

            void ReadMultiLineComment();
            void ReadSingleLineComment();

        public:
            Lexer();

            void Lex(Analysis::Structure::SourceFile* source);
    };
}

#endif
