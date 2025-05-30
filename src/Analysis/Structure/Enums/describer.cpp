#include "describer.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

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

    Describer FromNode(const IParseNode* const node)
    {
        auto final = Describer::None;

        const auto count = node->ChildCount();
        for (int i = 0; i < count; i++)
        {
            switch (node->GetChild(i)->Token().Kind())
            {
                case SyntaxKind::Ref:
                    final = final | Describer::Ref;
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
                case SyntaxKind::Const:
                    final = final | Describer::Const;
                    break;
                case SyntaxKind::Constexpr:
                    final = final | Describer::Constexpr;
                    break;
                case SyntaxKind::Entrypoint:
                    final = final | Describer::Entrypoint;
                    break;
                default:
                    break;
            }
        }

        return final;
    }

    string ToString(const Describer& describer)
    {
        if (describer == Describer::None) return "None";

        const auto shortValue = static_cast<short>(describer);
        std::string result;

        if (shortValue & static_cast<short>(Describer::Ref))
            result += "Ref, ";
        if (shortValue & static_cast<short>(Describer::Public))
            result += "Public, ";
        if (shortValue & static_cast<short>(Describer::Private))
            result += "Private, ";
        if (shortValue & static_cast<short>(Describer::Static))
            result += "Static, ";
        if (shortValue & static_cast<short>(Describer::Const))
            result += "Const, ";
        if (shortValue & static_cast<short>(Describer::Constexpr))
            result += "Constexpr, ";
        if (shortValue & static_cast<short>(Describer::Entrypoint))
            result += "Entrypoint, ";

        if (!result.empty())
            result.erase(result.size() - 2);

        return result;
    }
}