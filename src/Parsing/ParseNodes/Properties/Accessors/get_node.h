#ifndef GET_NODE_H
#define GET_NODE_H

#include "../../parse_node.h"
#include "../../Describers/describer_node.h"

namespace ParseNodes::Properties
{
    class GetNode final : public virtual FixedNodeCollection<2>
    {
        public:
            GetNode(const Describers::DescriberNode* describer, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
