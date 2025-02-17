#include "source_file_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    SourceFileNode::SourceFileNode() : NodeCollection()
    { }

    NodeType SourceFileNode::NodeType() const { return NodeType::Source; }

    unsigned long SourceFileNode::Index() const
    {
        if (!children.empty())
            return children[0]->Index();

        return 0;
    }
}
