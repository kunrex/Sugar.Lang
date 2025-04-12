#ifndef THIS_NODE_H
#define THIS_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Values
{
    class ThisNode final : public ParseNode
    {
        public:
            explicit ThisNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
