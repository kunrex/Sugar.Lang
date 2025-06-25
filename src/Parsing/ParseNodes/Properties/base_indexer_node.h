#ifndef BASE_INDEXER_NODE_H
#define BASE_INDEXER_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Properties
{
    class BaseIndexerNode final : public virtual FixedNodeCollection<5>
    {
        public:
            BaseIndexerNode(const IParseNode* describer, const IParseNode* type, const IParseNode* parameters, const IParseNode* get, const IParseNode* set, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
