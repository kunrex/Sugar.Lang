#include "syntax_kind.h"

using namespace std;

namespace Tokens::Enums
{
    std::string ToString(const SyntaxKind& syntaxKind)
    {
        switch (syntaxKind)
        {
            case SyntaxKind::Dot:
                return "Dot";
            case SyntaxKind::Comma:
                return "Comma";
            case SyntaxKind::Colon:
                return "Colon";
            case SyntaxKind::Semicolon:
                return "Semicolon";
            case SyntaxKind::QuestionMark:
                return "QuestionMark";
            case SyntaxKind::OpenBracket:
                return "OpenBracket";
            case SyntaxKind::CloseBracket:
                return "CloseBracket";
            case SyntaxKind::BoxOpenBracket:
                return "BoxOpenBracket";
            case SyntaxKind::BoxCloseBracket:
                return "BoxCloseBracket";
            case SyntaxKind::FlowerOpenBracket:
                return "FlowerOpenBracket";
            case SyntaxKind::FlowerCloseBracket:
                return "FlowerCloseBracket";
            case SyntaxKind::Constant:
                return "Constant";
            case SyntaxKind::Identifier:
                return "Identifier";
            case SyntaxKind::Print:
                return "Print";
            case SyntaxKind::Println:
                return "Println";
            case SyntaxKind::Input:
                return "Input";
            case SyntaxKind::Format:
                return "Format";
            case SyntaxKind::Create:
                return "Create";
            case SyntaxKind::Constructor:
                return "Constructor";
            case SyntaxKind::Let:
                return "Let";
            case SyntaxKind::This:
                return "This";
            case SyntaxKind::Get:
                return "Get";
            case SyntaxKind::Set:
                return "Set";
            case SyntaxKind::If:
                return "If";
            case SyntaxKind::Else:
                return "Else";
            case SyntaxKind::Elif:
                return "Elif";
            case SyntaxKind::Do:
                return "Do";
            case SyntaxKind::For:
                return "For";
            case SyntaxKind::While:
                return "While";
            case SyntaxKind::Enum:
                return "Enum";
            case SyntaxKind::Class:
                return "Class";
            case SyntaxKind::Struct:
                return "Struct";
            case SyntaxKind::Static:
                return "Static";
            case SyntaxKind::Break:
                return "Break";
            case SyntaxKind::Return:
                return "Return";
            case SyntaxKind::Continue:
                return "Continue";
            case SyntaxKind::Public:
                return "Public";
            case SyntaxKind::Private:
                return "Private";
            case SyntaxKind::Indexer:
                return "Indexer";
            case SyntaxKind::Implicit:
                return "Implicit";
            case SyntaxKind::Explicit:
                return "Explicit";
            case SyntaxKind::Operator:
                return "Operator";
            case SyntaxKind::ToString:
                return "ToString";
            case SyntaxKind::Throw:
                return "Throw";
            case SyntaxKind::Func:
                return "Func";
            case SyntaxKind::Action:
                return "Action";
            case SyntaxKind::Invoke:
                return "Invoke";
            case SyntaxKind::FuncRef:
                return "Function Reference";
            case SyntaxKind::True:
                return "True";
            case SyntaxKind::False:
                return "False";
            case SyntaxKind::Ref:
                return "Ref";
            case SyntaxKind::As:
                return "As";
            case SyntaxKind::Addition:
                return "Addition";
            case SyntaxKind::Subtraction:
                return "Subtraction";
            case SyntaxKind::Multiplication:
                return "Multiplication";
            case SyntaxKind::Division:
                return "Division";
            case SyntaxKind::Modulus:
                return "Modulus";
            case SyntaxKind::LeftShift:
                return "LeftShift";
            case SyntaxKind::RightShift:
                return "RightShift";
            case SyntaxKind::BitwiseOr:
                return "BitwiseOr";
            case SyntaxKind::BitwiseAnd:
                return "BitwiseAnd";
            case SyntaxKind::BitwiseXor:
                return "BitwiseXor";
            case SyntaxKind::BitwiseNot:
                return "BitwiseNot";
            case SyntaxKind::Increment:
                return "Increment";
            case SyntaxKind::Decrement:
                return "Decrement";
            case SyntaxKind::Not:
                return "Not";
            case SyntaxKind::Plus:
                return "Plus";
            case SyntaxKind::Minus:
                return "Minus";
            case SyntaxKind::Equals:
                return "Equals";
            case SyntaxKind::NotEquals:
                return "NotEquals";
            case SyntaxKind::LesserThan:
                return "LesserThan";
            case SyntaxKind::GreaterThan:
                return "GreaterThan";
            case SyntaxKind::LesserThanEquals:
                return "LesserThanEquals";
            case SyntaxKind::GreaterThanEquals:
                return "GreaterThanEquals";
            case SyntaxKind::Or:
                return "Or";
            case SyntaxKind::And:
                return "And";
            case SyntaxKind::Assignment:
                return "Assignment";
            case SyntaxKind::AssignmentAddition:
                return "AssignmentAddition";
            case SyntaxKind::AssignmentSubtraction:
                return "AssignmentSubtraction";
            case SyntaxKind::AssignmentMultiplication:
                return "AssignmentMultiplication";
            case SyntaxKind::AssignmentDivision:
                return "AssignmentDivision";
            case SyntaxKind::AssignmentModulus:
                return "AssignmentModulus";
            case SyntaxKind::AssignmentBitwiseOr:
                return "AssignmentBitwiseOr";
            case SyntaxKind::AssignmentBitwiseAnd:
                return "AssignmentBitwiseAnd";
            case SyntaxKind::AssignmentBitwiseXor:
                return "AssignmentBitwiseXor";
            case SyntaxKind::AssignmentBitwiseLeftShift:
                return "AssignmentBitwiseLeftShift";
            case SyntaxKind::AssignmentBitwiseRightShift:
                return "AssignmentBitwiseRightShift";
            case SyntaxKind::Short:
                return "Short";
            case SyntaxKind::Int:
                return "Int";
            case SyntaxKind::Long:
                return "Long";
            case SyntaxKind::Float:
                return "Float";
            case SyntaxKind::Double:
                return "Double";
            case SyntaxKind::Boolean:
                return "Boolean";
            case SyntaxKind::Character:
                return "Character";
            case SyntaxKind::Null:
                return "Null";
            case SyntaxKind::Void:
                return "Void";
            case SyntaxKind::Array:
                return "Array";
            case SyntaxKind::List:
                return "List";
            case SyntaxKind::Dictionary:
                return "Dictionary";
            case SyntaxKind::Tuple:
                return "Tuple";
            case SyntaxKind::Nullable:
                return "Nullable";
            case SyntaxKind::Exception:
                return "Exception";
            case SyntaxKind::String:
                return "String";
            case SyntaxKind::Object:
                return "Object";
            case SyntaxKind::Import:
                return "Import";
            default:
                return "Invalid";
        }
    }

    std::ostream& operator<<(std::ostream& os, const SyntaxKind& dt) { return os << ToString(dt); }
}
