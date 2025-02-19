#include "data_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::DataTypes
{
    DataTypeNode::DataTypeNode(const DescriberNode* const describer, const IdentifierNode* const identifier, const NodeCollection<ParseNode>* const body, const Token& keyword) : ParseNode(), DescribableNode(describer), NameableNode(identifier), body(body), keyword(keyword)
    { }

    const NodeCollection<ParseNode>* DataTypeNode::Body() const { return body; }

    unsigned long DataTypeNode::Index() const { return keyword.Index(); }

    DataTypeNode::~DataTypeNode()
    {
        delete body;
    }
}
