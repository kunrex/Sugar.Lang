#include "base_indexer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{

    BaseIndexerNode::BaseIndexerNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const GetNode* const get, const SetNode* const set, const Tokens::Token& keyword) : EntityNode(describer, type, keyword)
    {
        children.push_back(parameters);
        children.push_back(get);
        children.push_back(set);
    }

    NodeType BaseIndexerNode::NodeType() const { return NodeType::IndexerDeclaration; }
}
