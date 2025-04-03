#include "constant_compiler.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/Local/accessibility_exception.h"
#include "../../../Parsing/ParseNodes/Constants/constant_node.h"
#include "../../../Parsing/ParseNodes/Expressions/cast_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/dot_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Binary/binary_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Unary/unary_node.h"
#include "../../Creation/Binding/binder_extensions.h"
#include "../Context/context_node.h"
#include "../Core/Interfaces/Creation/i_constant.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../Wrappers/Reference/object.h"
#include "../Wrappers/Value/boolean.h"
#include "../Wrappers/Value/character.h"
#include "../Wrappers/Value/double.h"
#include "../Wrappers/Value/float.h"
#include "../Wrappers/Value/integer.h"
#include "../Wrappers/Value/long.h"
#include "../Wrappers/Value/short.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Compilation
{
    std::optional<long> BinaryOperation(const SyntaxKind operation, const long a, const long b)
    {
        switch (operation)
        {
            case SyntaxKind::Addition: return a + b;
            case SyntaxKind::Subtraction: return a - b;
            case SyntaxKind::Multiplication: return a * b;
            case SyntaxKind::Division: return b != 0 ? a / b : std::nullopt;
            case SyntaxKind::Modulus: return b != 0 ? a % b : std::nullopt;

            case SyntaxKind::BitwiseAnd: return a & b;
            case SyntaxKind::BitwiseOr: return a | b;
            case SyntaxKind::BitwiseXor: return a ^ b;
            case SyntaxKind::LeftShift: return a << b;
            case SyntaxKind::RightShift: return a >> b;

            case SyntaxKind::Equals:return a == b;
            case SyntaxKind::NotEquals:return a != b;
            case SyntaxKind::LesserThan:return a < b;
            case SyntaxKind::GreaterThan:return a > b;
            case SyntaxKind::LesserThanEquals:return a <= b;
            case SyntaxKind::GreaterThanEquals:return a >= b;
            default:
                //exception
                return std::nullopt;
        }
    }

    std::optional<double> BinaryOperation(const SyntaxKind operation, const double a, const double b)
    {
        switch (operation)
        {
            case SyntaxKind::Addition: return a + b;
            case SyntaxKind::Subtraction: return a - b;
            case SyntaxKind::Multiplication: return a * b;
            case SyntaxKind::Division: return b != 0.0 ? a / b : std::nullopt;

            case SyntaxKind::Equals: return a == b;
            case SyntaxKind::NotEquals: return a != b;
            case SyntaxKind::LesserThan: return a < b;
            case SyntaxKind::GreaterThan: return a > b;
            case SyntaxKind::LesserThanEquals: return a <= b;
            case SyntaxKind::GreaterThanEquals: return a >= b;
            default:
                //exception
                return std::nullopt;
        }
    }

    std::optional<long> UnaryOperation(const SyntaxKind operation, const long a)
    {
        switch (operation)
        {
            case SyntaxKind::Plus: return a;
            case SyntaxKind::Minus: return -a;
            case SyntaxKind::BitwiseNot: return ~a;
            case SyntaxKind::Not: return !a;
            default:
                //exception
                return std::nullopt;
        }
    }

    std::optional<double> UnaryOperation(const SyntaxKind operation, const double a)
    {
        switch (operation)
        {
            case SyntaxKind::Plus: return a;
            case SyntaxKind::Minus: return -a;
            case SyntaxKind::Not: return !a;
            default:
                //exception
                return std::nullopt;
        }
    }

    string Concat(const string& a, const string& b) { return a + b; }
    string StrMultiply(const string& a, const long b)
    {
        string result;
        for (auto i = 0; i < b; i++)
            result += a;

        return result;
    }

    const IDataType* BindDataType(const TypeKind typeKind)
    {

    }

    std::optional<CompilationResult> CompileExpression(const IParseNode* const parseNode, const IConstant* const constant, const IDataType* const dataType)
    {
        switch (parseNode->NodeType())
        {
            case NodeType::Dot:
                {

                }
                break;
            case NodeType::Constant:
                {
                    const auto token = parseNode->Token();
                    switch (token.Kind())
                    {
                        case SyntaxKind::Short:
                        case SyntaxKind::Int:
                        case SyntaxKind::Long:
                        case SyntaxKind::Character:
                        case SyntaxKind::Boolean:
                            return CompilationResult(static_cast<TypeKind>(token.Kind()), *token.Value<long>());
                        case SyntaxKind::Float:
                        case SyntaxKind::Double:
                            return CompilationResult(static_cast<TypeKind>(token.Kind()), *token.Value<double>());
                        case SyntaxKind::String:
                            return CompilationResult(static_cast<TypeKind>(token.Kind()), *token.Value<string>());
                        default:
                            //exception
                            return std::nullopt;
                    }
                }
            case NodeType::Identifier:
                {
                    switch (const auto characteristic = dataType->FindCharacteristic(*parseNode->Token().Value<string>()); characteristic->MemberType())
                    {
                        case MemberType::EnumField:
                        case MemberType::ConstantField:
                            {
                                const auto constField = dynamic_cast<const IConstant*>(characteristic);
                                constant->PushDependency(constField);

                                if (!constField->Readable())
                                    CompileExpression(constField, dataType);

                                if (!constField->Readable())
                                {
                                    //exception
                                    return std::nullopt;
                                }

                                return constField->AsCompiledExpression();
                            }
                            break;
                        default:
                            //exception
                            return std::nullopt;
                    }
                }
                break;
            case NodeType::Unary:
                {
                    const auto operand = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::Expression)), constant, dataType);
                    if (!operand)
                        return std::nullopt;

                    if (const auto operation = parseNode->Token().Kind(); BindDataType(operand->creationType)->FindOverload(operation))
                    {
                        switch (operand->creationType)
                        {
                            case SyntaxKind::Short:
                            case SyntaxKind::Int:
                            case SyntaxKind::Long:
                            case SyntaxKind::Character:
                            case SyntaxKind::Boolean:
                                return UnaryOperation(operation, std::get<long>(operand.value));
                            case SyntaxKind::Float:
                            case SyntaxKind::Double:
                                return UnaryOperation(operation, std::get<double>(operand.value));
                            default:
                                //exception
                                    return std::nullopt;
                        }
                    }

                    //exception
                    return std::nullopt;
                }
                break;
            case NodeType::Binary:
                {
                    const auto lhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::LHS)), constant, dataType);
                    if (!lhs)
                        return std::nullopt;

                    const auto rhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::RHS)), constant, dataType);
                    if (!rhs)
                        return std::nullopt;

                    if (lhs->creationType == rhs->creationType)
                    {
                        if (const auto operation = parseNode->Token().Kind(); BindDataType(lhs->creationType)->FindOverload(operation))
                        {
                            switch (lhs->creationType)
                            {
                                case SyntaxKind::Short:
                                case SyntaxKind::Int:
                                case SyntaxKind::Long:
                                case SyntaxKind::Character:
                                case SyntaxKind::Boolean:
                                    return BinaryOperation(operation, std::get<long>(lhs.value), std::get<long>(rhs.value));
                                case SyntaxKind::Float:
                                case SyntaxKind::Double:
                                    return BinaryOperation(operation, std::get<double>(lhs.value), std::get<double>(rhs.value));
                                case SyntaxKind::String:
                                    {
                                        if (operation == SyntaxKind::Addition)
                                            return CompilationResult(TypeKind::String, Concat(std::get<string>(lhs.value), std::get<string>(rhs.value)));

                                        return CompilationResult(TypeKind::String, StrMultiply(std::get<string>(lhs.value), std::get<long>(rhs.value)));
                                    }
                                default:
                                    //exception
                                    return std::nullopt;
                            }
                        }
                    }

                    //exception
                    return std::nullopt;
                }
                break;
        }
    }

    void CompileExpression(const IConstant* const constant, const IDataType* const dataType)
    {
        CompileExpression(constant->ParseNode(), constant, dataType);
    }
}
