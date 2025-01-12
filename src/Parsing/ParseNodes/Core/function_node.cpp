#include "function_node.h"

using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    FunctionNode::FunctionNode(const DescriberNode* describer, const ParseNode* type, const CompoundDeclarationNode* parameters, const ParseNode* body) : DescribableNode(describer), EntityNode(type), BodyNode(body), parameters(parameters)
    { }

    const CompoundDeclarationNode* FunctionNode::Parameters() const { return parameters; }

    FunctionNode::~FunctionNode()
    {
        delete parameters;
    }
}
