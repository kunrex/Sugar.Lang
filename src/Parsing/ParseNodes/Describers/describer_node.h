#ifndef DESCRIBER_NODE_H
#define DESCRIBER_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Describers
{
    class DescriberNode final : public DynamicNodeCollection
    {
        public:
            explicit DescriberNode(const Tokens::Token& openBracket);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
