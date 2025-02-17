#include "keyword_function_node.h"

using namespace Tokens;

using namespace ParseNodes::Groups;

namespace ParseNodes::Functions::Creation
{
    KeywordFunctionNode::KeywordFunctionNode(const Describers::DescriberNode* describer, const ParseNode* type, const CompoundDeclarationNode* parameters, const ScopeNode* body, const Token& keyword) : FunctionNode(describer, type, parameters, body), keyword(keyword)
    { }

    unsigned long KeywordFunctionNode::Index() const { return keyword.Index(); }
}
