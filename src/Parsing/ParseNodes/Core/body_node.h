#ifndef BODY_NODE
#define BODY_NODE

#include "../Groups/scope_node.h"

namespace ParseNodes::Core
{
    class BodyNode
    {
        protected:
            const Groups::ScopeNode* body;

            explicit BodyNode(const Groups::ScopeNode* body);

        public:
            [[nodiscard]] const Groups::ScopeNode* Body() const;

            virtual ~BodyNode();
    };
}

#endif
