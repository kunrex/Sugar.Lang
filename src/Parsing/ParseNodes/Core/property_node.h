#ifndef PROPERTY_NODE_H
#define PROPERTY_NODE_H

#include "../Properties/Accessors/get_node.h"
#include "../Properties/Accessors/set_node.h"

namespace ParseNodes::Core
{
    class PropertyNode
    {
        protected:
            const Properties::GetNode* get;
            const Properties::SetNode* set;

        public:
            PropertyNode(const Properties::GetNode* get, const Properties::SetNode* set);

            [[nodiscard]] const Properties::GetNode* Get() const;
            [[nodiscard]] const Properties::SetNode* Set() const;

            virtual ~PropertyNode();
    };
}

#endif
