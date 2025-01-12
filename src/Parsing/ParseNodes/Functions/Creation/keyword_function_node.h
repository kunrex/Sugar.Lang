#ifndef KEYWORD_FUNCTION_NODE_H
#define KEYWORD_FUNCTION_NODE_H

#include "../../parse_node.h"
#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class KeywordFunctionNode : public ParseNode, Core::FunctionNode
    {
        protected:
            const Tokens::Token& keyword;

            KeywordFunctionNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const ParseNode* body, const Tokens::Token& keyword);
    };
}

#endif
