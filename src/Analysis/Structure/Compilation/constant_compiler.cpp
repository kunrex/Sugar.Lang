#include "constant_compiler.h"

#include "compilation_result.h"
#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/Local/accessibility_exception.h"
#include "../../../Parsing/ParseNodes/Constants/constant_node.h"
#include "../../../Parsing/ParseNodes/Expressions/cast_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/dot_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Binary/binary_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Unary/unary_node.h"
#include "../../Creation/Binding/binder_extensions.h"
#include "../Context/context_node.h"
#include "../Context/Constants/float_constant.h"
#include "../Context/Constants/integer_constant.h"
#include "../Context/Constants/string_constant.h"
#include "../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../Core/Interfaces/Creation/i_constant.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../Wrappers/Reference/object.h"
#include "../Wrappers/Reference/string.h"
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

using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Compilation
{
    const IPrimitiveType* BindPrimitiveType(const IParseNode* const node)
    {
        switch (node->Token().Kind())
        {
        case SyntaxKind::Short:
            return &Short::Instance();
        case SyntaxKind::Int:
            return &Integer::Instance();
        case SyntaxKind::Long:
            return &Long::Instance();
        case SyntaxKind::Float:
            return &Float::Instance();
        case SyntaxKind::Double:
            return &Double::Instance();
        case SyntaxKind::String:
            return &String::Instance();
        case SyntaxKind::Character:
            return &Character::Instance();
        default:
            return &Boolean::Instance();
        }
    }

    std::optional<CompilationResult> AsCompilationResult(const IConstant* const constant)
    {
        switch (constant->CreationType()->Type())
        {
            case TypeKind::Short:
                return CompilationResult(&Short::Instance(), *reinterpret_cast<const short*>(constant->Context()->Metadata()));
            case TypeKind::Int:
            case TypeKind::EnumField:
                return CompilationResult(&Integer::Instance(), *reinterpret_cast<const int*>(constant->Context()->Metadata()));
            case TypeKind::Long:
                return CompilationResult(&Long::Instance(), *reinterpret_cast<const long*>(constant->Context()->Metadata()));
            case TypeKind::Float:
                return CompilationResult(&Float::Instance(), *reinterpret_cast<const float*>(constant->Context()->Metadata()));
            case TypeKind::Double:
                return CompilationResult(&Double::Instance(), *reinterpret_cast<const double*>(constant->Context()->Metadata()));
            case TypeKind::Boolean:
                return CompilationResult(&Boolean::Instance(), *reinterpret_cast<const bool*>(constant->Context()->Metadata()));
            case TypeKind::Character:
                return CompilationResult(&Character::Instance(), *reinterpret_cast<const char*>(constant->Context()->Metadata()));
            case TypeKind::String:
                return CompilationResult(&String::Instance(), *reinterpret_cast<const string*>(constant->Context()->Metadata()));
            default:
                return std::nullopt;
        }
    }

    std::optional<CompilationResult> TryCompileConstant(const IParseNode* const identifierNode, const IConstant* const constant, const IDataType* const creationType, const IUserDefinedType* const dataType)
    {
        switch (const auto characteristic = creationType->FindCharacteristic(*identifierNode->Token().Value<string>()); characteristic->MemberType())
        {
            case MemberType::ConstantField:
                {
                    const auto constField = dynamic_cast<const IConstant*>(characteristic);
                    if (constField->IsDependent(constant))
                    {
                        //exception
                        return std::nullopt;
                    }

                    constant->PushDependency(constField);

                    if (!constField->Compiled())
                        CompileExpression(constField, dataType);

                    return AsCompilationResult(constField);
                }
                break;
            default:
                //exception
                return std::nullopt;
        }
    }

    std::optional<CompilationResult> CompileExpression(const IParseNode* const parseNode, const IConstant* const constant, const IUserDefinedType* const dataType)
    {
        switch (parseNode->NodeType())
        {
            case NodeType::Dot:
                {
                    const IDataType* currentType = dataType;
                    auto current = parseNode;

                    while (true)
                    {
                        if (current->NodeType() == NodeType::Identifier)
                            return TryCompileConstant(current, constant, currentType, dataType);

                        if (current->NodeType() != NodeType::Dot)
                        {
                            //exception
                            return std::nullopt;
                        }

                        if (const auto lhs = parseNode->GetChild(static_cast<int>(ChildCode::LHS)); lhs->NodeType() == NodeType::Identifier)
                        {
                            const auto characteristic = currentType->FindCharacteristic(*lhs->Token().Value<string>());
                            if (characteristic == nullptr)
                            {
                                //exception
                                return std::nullopt;
                            }

                            currentType = characteristic->CreationType();
                        }

                        //exception
                        return std::nullopt;
                    }
                }
                break;
            case NodeType::Constant:
                {
                    switch (const auto& token = parseNode->Token(); token.Kind())
                    {
                        case SyntaxKind::Short:
                                return CompilationResult(&Short::Instance(), *token.Value<long>());
                            case SyntaxKind::Int:
                                return CompilationResult(&Integer::Instance(), *token.Value<long>());
                            case SyntaxKind::Long:
                                return CompilationResult(&Long::Instance(), *token.Value<long>());
                            case SyntaxKind::Character:
                                return CompilationResult(&Character::Instance(), *token.Value<long>());
                            case SyntaxKind::Boolean:
                                return CompilationResult(&Boolean::Instance(), *token.Value<long>());
                            case SyntaxKind::Float:
                                return CompilationResult(&Float::Instance(), *token.Value<long>());
                            case SyntaxKind::Double:
                                return CompilationResult(&Double::Instance(), *token.Value<long>());
                            case SyntaxKind::String:
                                return CompilationResult(&String::Instance(), *token.Value<long>());
                            default:
                                //exception
                                return std::nullopt;
                    }
                }
            case NodeType::Identifier:
                return TryCompileConstant(parseNode, constant, dataType, dataType);
            case NodeType::Cast:
                {
                    const auto operand = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::Expression)), constant, dataType);
                    if (!operand)
                        return std::nullopt;

                    const auto type = BindPrimitiveType(parseNode->GetChild(static_cast<int>(ChildCode::RHS)));

                    if (const auto cast = operand->creationType->FindBuiltInCast(type, operand->creationType); cast != nullptr)
                        return cast->StaticCompile(*operand);

                    //exception
                    return std::nullopt;
                }
            case NodeType::Unary:
                {
                    const auto operand = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::Expression)), constant, dataType);
                    if (!operand)
                        return std::nullopt;

                    const auto operation = parseNode->Token().Kind();
                    if (operation == SyntaxKind::Increment || operation == SyntaxKind::Decrement)
                    {
                        //exception
                        return std::nullopt;
                    }

                    const auto overload = operand->creationType->FindBuiltInOverload(operation);

                    if (overload == nullptr)
                    {
                        //exception;
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *operand });
                }
                break;
            case NodeType::Binary:
                {
                    const auto lhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::LHS)), constant, dataType);
                    if (!lhs)
                        return std::nullopt;

                    const auto rhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::RHS)), constant, dataType);
                    if (!rhs) {
                        return std::nullopt;
                    }

                    if (lhs->creationType != rhs->creationType)
                    {
                        //exception
                        return std::nullopt;
                    }

                    const auto overload = lhs->creationType->FindBuiltInOverload(parseNode->Token().Kind());

                    if (overload == nullptr)
                    {
                        //exception;
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *lhs, *rhs });
                }
            default:
                //exception
                return std::nullopt;
        }
    }

    const IContextNode* CompileExpression(const IConstant* const constant, const IUserDefinedType* const dataType)
    {
        const auto result = CompileExpression(constant->ParseNode(), constant, dataType);
        if (!result)
            return nullptr;

        switch (result->creationType->Type())
        {
            case TypeKind::Short:
                return new ShortConstant(std::get<short>(result->data));
            case TypeKind::Int:
                return new IntegerConstant(std::get<int>(result->data));
            case TypeKind::Long:
                return new LongConstant(std::get<long>(result->data));
            case TypeKind::Float:
                return new FloatConstant(std::get<float>(result->data));
            case TypeKind::Double:
                return new DoubleConstant(std::get<double>(result->data));
            case TypeKind::Boolean:
                {
                    if (std::get<bool>(result->data))
                        return new TrueConstant();

                    return new FalseConstant();
                }
            case TypeKind::Character:
                return new CharacterConstant(std::get<char>(result->data));
            case TypeKind::String:
                return new StringConstant(std::get<string>(result->data));
            default:
                return nullptr;
        }
    }
}
