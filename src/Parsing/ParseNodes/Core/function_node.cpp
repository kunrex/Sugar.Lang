#include "function_node.h"

using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    FunctionNode::FunctionNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const NodeCollection<ParseNode>* const body) : DescribableNode(describer), EntityNode(type), BodyNode(body), parameters(parameters)
    { }

    const CompoundDeclarationNode* FunctionNode::Parameters() const { return parameters; }

    FunctionNode::~FunctionNode()
    {
        delete parameters;
    }
}
