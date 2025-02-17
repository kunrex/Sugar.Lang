#include "describer.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Describers;

namespace Analysis::Structure::Enums
{
    Describer operator&(const Describer& lhs, const Describer& rhs)
    {
        return static_cast<Describer>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    Describer operator|(const Describer& lhs, const Describer& rhs)
    {
        return static_cast<Describer>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }

    Describer FromNode(const DescriberNode* const node)
    {
        auto final = Describer::None;
        for (int i = 0; i < node->TokenCount(); i++)
        {
            switch (node->TokenAt(i).Kind())
            {
                case SyntaxKind::Ref:
                    final = final | Describer::Ref;
                    break;
                case SyntaxKind::Const:
                    final = final | Describer::Const;
                    break;
                case SyntaxKind::Static:
                    final = final | Describer::Static;
                    break;
                case SyntaxKind::Public:
                    final = final | Describer::Public;
                    break;
                case SyntaxKind::Private:
                    if ((final & Describer::Public) != Describer::Public)
                        final = final | Describer::Private;
                    break;
                default:
                    break;
            }
        }

        return final;
    }
}