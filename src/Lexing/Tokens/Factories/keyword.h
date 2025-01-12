#ifndef KEYWORD_H
#define KEYWORD_H

#include <map>
#include <optional>

#include "../token.h"
#include "../Enums/keyword_type.h"

namespace Tokens
{
    class Keyword final
    {
        private:
            static std::unordered_map<std::string, std::tuple<Enums::SyntaxKind, Enums::KeywordType>> keywordMap;

            Keyword();
            static void KeywordInit();

        public:
            static std::optional<Token> TryMatchKeyword(const std::string& value, unsigned long i);
    };
}

#endif
