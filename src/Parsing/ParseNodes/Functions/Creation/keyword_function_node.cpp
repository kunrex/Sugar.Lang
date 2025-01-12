#include "keyword_function_node.h"

using namespace Tokens;

namespace ParseNodes::Functions::Creation
{
    KeywordFunctionNode::KeywordFunctionNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const ParseNode* body, const Token& keyword) : FunctionNode(describer, type, parameters, body), keyword(keyword)
    { }
}
