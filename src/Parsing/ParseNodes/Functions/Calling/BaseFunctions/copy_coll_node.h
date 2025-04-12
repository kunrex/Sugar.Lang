#ifndef COPY_COLL_NODE_H
#define COPY_COLL_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class CopyCallNode final : public DynamicNodeCollection
    {
        public:
            explicit CopyCallNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
