#ifndef BODY_NODE
#define BODY_NODE

#include "Interfaces/i_body_node.h"

namespace ParseNodes::Core
{
    class BodyNode : public virtual Interfaces::IBodyNode
    {
        protected:
            const NodeCollection<ParseNode>* body;

            explicit BodyNode(const NodeCollection<ParseNode>* body);

        public:
            [[nodiscard]] const NodeCollection<ParseNode>* Body() const override;

            ~BodyNode() override;
    };
}

#endif
