#include "data_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::DataTypes
{
    DataTypeNode::DataTypeNode(const DescriberNode* const describer, const IdentifierNode* const identifier, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword), DescribableNode(describer), NameableNode(identifier), BodyNode(body)
    { }
}
