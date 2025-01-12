#ifndef GENERIC_TYPE_NODE_H
#define GENERIC_TYPE_NODE_H

#include "../keyword_type_node.h"
#include "../../../Groups/generic_node.h"

namespace ParseNodes::Types
{
    class GenericTypeNode : public KeywordTypeNode
    {
        protected:
            const Groups::GenericNode* generic;

            GenericTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

        public:
            [[nodiscard]] const Groups::GenericNode* Generic() const;

            ~GenericTypeNode() override;
    };
}

#endif
