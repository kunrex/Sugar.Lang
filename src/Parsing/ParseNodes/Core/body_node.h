#ifndef BODY_NODE
#define BODY_NODE

#include "../parse_node.h"

namespace ParseNodes::Core
{
    class BodyNode
    {
        protected:
            const ParseNode* body;

            explicit BodyNode(const ParseNode* body);

        public:
            [[nodiscard]] const ParseNode* Body() const;

            virtual ~BodyNode();
    };
}

#endif
