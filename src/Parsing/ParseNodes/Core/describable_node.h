#ifndef DESCRIBABLE_NODE_H
#define DESCRIBABLE_NODE_H

#include "Interfaces/i_describable_node.h"

namespace ParseNodes::Core
{
    class DescribableNode : public virtual Interfaces::IDescribableNode
    {
        protected:
            const Describers::DescriberNode* describer;

            explicit DescribableNode(const Describers::DescriberNode* describer);

        public:
            [[nodiscard]] const Describers::DescriberNode* Describer() const override;

            ~DescribableNode() override;
    };
}

#endif
