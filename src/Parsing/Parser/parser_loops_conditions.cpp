#include "parser.h"

#include "../ParseNodes/Conditions/if_node.h"
#include "../ParseNodes/Conditions/else_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Loops;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Conditions;

namespace Parsing
{
    const IfChainNode* Parser::ParseIf()
    {
        bool flag = false;

        const auto chain = new IfChainNode(Current());
        for (; index < source->TokenCount(); index++)
        {
            const auto& keyword = Current();
            index++;

            switch (keyword.Kind())
            {
                case SyntaxKind::If:
                    {
                        if (flag)
                        {
                            index -= 2;
                            flag = false;
                            break;
                        }

                        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);
                        const auto condition = ParseNonEmptyExpression(SeparatorKind::CloseBracket);
                        TryMatchToken(Current(), SyntaxKind::CloseBracket, true);

                        const auto body = ParseLazyScope();

                        chain->AddChild(new IfNode(condition, body, keyword));
                        flag = true;
                    }
                    break;
                case SyntaxKind::Elif:
                    {
                        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);
                        const auto condition = ParseNonEmptyExpression(SeparatorKind::CloseBracket);
                        TryMatchToken(Current(), SyntaxKind::CloseBracket, true);

                        const auto body = ParseLazyScope();

                        chain->AddChild(new IfNode(condition, body, keyword));
                    }
                    break;
                case SyntaxKind::Else:
                    {
                        flag = false;
                        chain->AddChild(new ElseNode(ParseLazyScope(), keyword));;
                    }
                    break;
                default:
                    flag = false;
                    break;
            }

            if (!flag)
                break;
        }

        return chain;
    }

    const WhileNode* Parser::ParseWhile()
    {
        const auto& keyword = Current();
        index++;

        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);

        const auto condition = ParseNonEmptyExpression(SeparatorKind::CloseBracket);
        TryMatchToken(Current(), SyntaxKind::CloseBracket, true);

        const auto body = ParseLazyScope();
        return new WhileNode(condition, body, keyword);
    }

    const DoWhileNode* Parser::ParseDoWhile()
    {
        const auto& keyword = Current();
        index++;

        const auto body = ParseLazyScope();
        index++;

        TryMatchToken(Current(), SyntaxKind::While, true);
        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);

        const auto condition = ParseNonEmptyExpression(SeparatorKind::CloseBracket);
        return new DoWhileNode(condition, body, keyword);
    }

    const ForLoopNode* Parser::ParseForLoop()
    {
        const auto& keyword = Current();
        index++;

        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);

        const auto pre = ParseStatement();
        TryMatchToken(Current(), SyntaxKind::Semicolon, true);

        const auto condition = ParseExpression(SeparatorKind::Semicolon);
        TryMatchToken(Current(), SyntaxKind::Semicolon, true);

        const auto post = ParseExpression(SeparatorKind::CloseBracket);
        TryMatchToken(Current(), SyntaxKind::CloseBracket, true);

        const auto body = ParseLazyScope();
        return new ForLoopNode(pre, condition, post, body, keyword);
    }
}