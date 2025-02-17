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
            const unsigned long index;
            std::vector<const Tokens::Token*> tokens;

        public:
            explicit DescriberNode(unsigned long index);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void PushToken(const Tokens::Token* token);

            [[nodiscard]] unsigned long TokenCount() const;
            [[nodiscard]] const Tokens::Token& TokenAt(int i) const;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
