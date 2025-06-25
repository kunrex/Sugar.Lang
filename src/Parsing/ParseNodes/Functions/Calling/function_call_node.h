#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class FunctionCallNode final : public DynamicNodeCollection
    {
        public:
            explicit FunctionCallNode(const IParseNode* identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
