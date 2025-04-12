#ifndef DESCRIBER_KEYWORD_NODE_H
#define DESCRIBER_KEYWORD_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Describers
{
    class DescriberKeywordNode final : public ParseNode
    {
        public:
            explicit DescriberKeywordNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
