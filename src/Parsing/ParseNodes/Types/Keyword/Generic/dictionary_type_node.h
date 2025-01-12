#ifndef DICTIONARY_TYPE_NODE_H
#define DICTIONARY_TYPE_NODE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class DictionaryTypeNode final : public GenericTypeNode
    {
        public:
            DictionaryTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
