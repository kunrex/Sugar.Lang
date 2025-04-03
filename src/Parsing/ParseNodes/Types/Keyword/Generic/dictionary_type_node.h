#ifndef DICTIONARY_TYPE_NODE_H
#define DICTIONARY_TYPE_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class DictionaryTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit DictionaryTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
