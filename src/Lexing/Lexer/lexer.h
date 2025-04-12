#ifndef LEXER_H
#define LEXER_H

#include "../../Services/singleton_service.h"

#include "../../Analysis/Structure/source_file.h"

namespace Lexing
{
    class Lexer final : public Services::SingletonService
    {
        private:
            unsigned long index;
            Analysis::Structure::SourceFile* source;

            [[nodiscard]] char LookAhead() const;

            void ReadString();
            void ReadNumber();
            void ReadIdentifier();
            void ReadCharacter();

            void ReadMultiLineComment();
            void ReadSingleLineComment();

            Lexer();

        public:
            static Lexer& Instance();

            void Lex(Analysis::Structure::SourceFile* source);
    };
}

#endif
