#include "set_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    SetNode::SetNode(const DescriberNode* const describer, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Body, body);
    }

    NodeType SetNode::NodeType() const { return NodeType::Set; }

    void SetNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Set Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
