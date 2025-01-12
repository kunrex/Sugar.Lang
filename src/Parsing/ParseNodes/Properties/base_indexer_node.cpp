#include "base_indexer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BaseIndexerNode::BaseIndexerNode(const DescriberNode* describer, const ParseNode* type, const CompoundDeclarationNode* parameters, const GetNode* get, const SetNode* set, const Token& keyword) : DescribableNode(describer), EntityNode(type), PropertyNode(get, set), parameters(parameters), keyword(keyword)
    { }

    NodeType BaseIndexerNode::NodeType() const { return NodeType::IndexerDeclaration; }

    const CompoundDeclarationNode* BaseIndexerNode::Parameters() const { return parameters; }

    const Token& BaseIndexerNode::Keyword() const { return keyword; }

    BaseIndexerNode::~BaseIndexerNode()
    {
        delete parameters;
    }
}
