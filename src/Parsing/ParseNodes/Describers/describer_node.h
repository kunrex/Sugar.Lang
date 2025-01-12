#ifndef DESCRIBER_NODE_H
#define DESCRIBER_NODE_H

#include <vector>

#include "../parse_node.h"
#include "../../../Lexing/Tokens/token.h"

namespace ParseNodes::Describers
{
    class DescriberNode final : public ParseNode
    {
        private:
            std::vector<const Tokens::Token*> tokens;

        public:
            DescriberNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void PushToken(const Tokens::Token* token);

            [[nodiscard]] int TokenCount() const;
            [[nodiscard]] const Tokens::Token& TokenAt(int i) const;
    };
}

#endif
