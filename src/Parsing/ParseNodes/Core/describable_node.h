#ifndef DESCRIBABLE_NODE_H
#define DESCRIBABLE_NODE_H

#include "../Describers/describer_node.h"

namespace ParseNodes::Core
{
    class DescribableNode
    {
        protected:
            const Describers::DescriberNode* describer;

            explicit DescribableNode(const Describers::DescriberNode* describer);

        public:
            [[nodiscard]] const Describers::DescriberNode* Describer() const;

            virtual ~DescribableNode();
    };
}

#endif
