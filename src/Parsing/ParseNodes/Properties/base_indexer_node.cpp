#include "base_indexer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BaseIndexerNode::BaseIndexerNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const GetNode* const get, const SetNode* const set, const Token& keyword) : DescribableNode(describer), EntityNode(type), PropertyNode(get, set), parameters(parameters), keyword(keyword)
    { }

    NodeType BaseIndexerNode::NodeType() const { return NodeType::IndexerDeclaration; }

    const CompoundDeclarationNode* BaseIndexerNode::Parameters() const { return parameters; }

    unsigned long BaseIndexerNode::Index() const { return keyword.Index(); }

    BaseIndexerNode::~BaseIndexerNode()
    {
        delete parameters;
    }
}
