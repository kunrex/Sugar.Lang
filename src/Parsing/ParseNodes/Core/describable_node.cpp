#include "describable_node.h"

namespace ParseNodes::Core
{
    DescribableNode::DescribableNode(const Describers::DescriberNode* describer) : describer(describer)
    { }

    const Describers::DescriberNode* DescribableNode::Name() const { return describer; }

    DescribableNode::~DescribableNode()
    {
        delete describer;
    }
}
