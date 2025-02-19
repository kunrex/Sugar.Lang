#include "keyword_function_node.h"

using namespace Tokens;

using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    KeywordFunctionNode::KeywordFunctionNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const ScopeNode* const body, const Token& keyword) : FunctionNode(describer, type, parameters, body), keyword(keyword)
    { }

    unsigned long KeywordFunctionNode::Index() const { return keyword.Index(); }
}
