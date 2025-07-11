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

        if ((shortValue & static_cast<short>(Describer::Ref)) == static_cast<short>(Describer::Ref))
            result.append("ref, ");
        if ((shortValue & static_cast<short>(Describer::Public)) == static_cast<short>(Describer::Public))
            result.append("public, ");
        if ((shortValue & static_cast<short>(Describer::Private)) == static_cast<short>(Describer::Private))
            result.append("private, ");
        if ((shortValue & static_cast<short>(Describer::Static)) == static_cast<short>(Describer::Static))
            result.append("static, ");
        if ((shortValue & static_cast<short>(Describer::Const)) == static_cast<short>(Describer::Const))
            result.append("const, ");
        if ((shortValue & static_cast<short>(Describer::Constexpr)) == static_cast<short>(Describer::Constexpr))
            result.append("constexpr, ");
        if ((shortValue & static_cast<short>(Describer::Entrypoint)) == static_cast<short>(Describer::Entrypoint))
            result.append("entrypoint, ");

        if (!result.empty())
            result.erase(result.size() - 2);

        return result;
    }
}