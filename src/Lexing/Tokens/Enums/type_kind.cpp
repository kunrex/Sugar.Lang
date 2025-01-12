#include "type_kind.h"

using namespace std;

namespace Tokens::Enums
{
    string ToString(const TypeKind& typeKind)
    {
        switch (typeKind)
        {
            case TypeKind::Short:
                return "Short";
            case TypeKind::Int:
                return "Integer";
            case TypeKind::Long:
                return "Long";
            case TypeKind::Float:
                return "Float";
            case TypeKind::Double:
                return "Double";
            case TypeKind::Boolean:
                return "Boolean";
            case TypeKind::Character:
                return "Character";
            case TypeKind::String:
                return "String";
            case TypeKind::Array:
                return "Array";
            case TypeKind::List:
                return "List";
            case TypeKind::Dictionary:
                return "Dictionary";
            case TypeKind::Tuple:
                return "Tuple";
            case TypeKind::Nullable:
                return "Nullable";
            case TypeKind::Exception:
                return "Exception";
            default:
                return "Object";
        }
    }

    ostream& operator << (std::ostream& os, const TypeKind& dt) { return os << ToString(dt); }
}