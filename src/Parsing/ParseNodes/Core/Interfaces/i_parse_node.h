#ifndef I_PARSE_NODE_H
#define I_PARSE_NODE_H

#include "../../Enums/node_type.h"

#include "../../../../Services/child.h"
#include "../../../../Services/printable.h"

#include "../../../../Lexing/Tokens/token.h"

namespace ParseNodes
{
    class ParseNode;

    template <int childCount>
    class FixedNodeCollection;
}

namespace ParseNodes::Core::Interfaces
{
    class IParseNode : public Services::Printable, public Services::ConstantChild<IParseNode>
    {
        public:
            [[nodiscard]] virtual Enums::NodeType NodeType() const = 0;

            [[nodiscard]] virtual const Tokens::Token& Token() const = 0;

            [[nodiscard]] virtual int ChildCount() const = 0;
            [[nodiscard]] virtual const IParseNode* GetChild(int index) const = 0;
    };
}

#endif
