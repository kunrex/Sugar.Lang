#include "type_kind.h"

namespace Tokens::Enums
{
    std::string ToString(const TypeKind& kind)
    {
        switch (kind)
        {
            case TypeKind::Short:
                return "Short";
            case TypeKind::Int:
                return "Int";
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
            case TypeKind::Array:
                return "Array";
            case TypeKind::List:
                return "List";
            case TypeKind::Dictionary:
                return "Dictionary";
            case TypeKind::Tuple:
                return "Tuple";
            case TypeKind::Func:
                return "Func";
            case TypeKind::Action:
                return "Action";
            case TypeKind::Nullable:
                return "Nullable";
            case TypeKind::Math:
                return "Math";
            case TypeKind::String:
                return "String";
            case TypeKind::Exception:
                return "Exception";
            case TypeKind::Object:
                return "Object";
            case TypeKind::Void:
                return "Void";
            case TypeKind::Custom:
                return "Custom";
            case TypeKind::EnumField:
                return "EnumField";
            case TypeKind::Referenced:
                return "Referenced";
            default:
                return "Unknown";
        }
    }
}