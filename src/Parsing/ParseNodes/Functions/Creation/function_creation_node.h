#ifndef FUNCTION_CREATION_NODE_H
#define FUNCTION_CREATION_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Creation
{
    class FunctionCreationNode final : public virtual FixedNodeCollection<5>
    {
        public:
            FunctionCreationNode(const IParseNode* describer, const IParseNode* type, const IParseNode* identifier, const IParseNode* parameters, const IParseNode* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
