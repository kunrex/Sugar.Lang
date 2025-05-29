#include "constant_binder.h"

#include <format>

#include "binder_extensions.h"
#include "../../../Exceptions/Compilation/Analysis/Local/constant_expected_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/overload_not_found_exception.h"
#include "../../Structure/Context/Constants/float_constant.h"
#include "../../Structure/Context/Constants/integer_constant.h"
#include "../../Structure/Context/Constants/string_constant.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_primitive_type.h"
#include "../../Structure/Wrappers/Generic/action.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Value/character.h"
#include "../../Structure/Wrappers/Value/double.h"
#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/integer.h"
#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/short.h"

#include "../../Structure/Compilation/compilation_result.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Creation::Binding
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

    std::optional<CompilationResult> AsCompilationResult(const ICharacteristic* const constant)
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
                return CompilationResult(&String::Instance(), *reinterpret_cast<const std::string*>(constant->Context()->Metadata()));
            default:
                return std::nullopt;
        }
    }

    std::optional<CompilationResult> TryCompileConstant(const IParseNode* const identifierNode, ICharacteristic* const constant, const IDataType* const creationType, const IUserDefinedType* const dataType)
    {
        switch (const auto characteristic = creationType->FindCharacteristic(*identifierNode->Token().Value<std::string>()); characteristic->MemberType())
        {
            case MemberType::ConstantField:
                {
                    if (characteristic->Context() != nullptr)
                        return AsCompilationResult(characteristic);

                    if (characteristic->HasDependant(constant))
                    {
                        PushException(new LogException(std::format("Cyclic dependency between: {} and: {}", constant->FullName(), characteristic->FullName()), identifierNode->Token().Index(), dataType->Parent()));
                        constant->IncrementDependencyCount();
                    }
                    else
                         characteristic->PushDependant(constant);
                }
                break;
            default:
                PushException(new ConstantNotFoundException(identifierNode->Token().Index(), dataType->Parent()));
                break;
        }

        return std::nullopt;
    }

    std::optional<CompilationResult> CompileEntity(const IParseNode* const parseNode, ICharacteristic* const constant, const IUserDefinedType* const dataType)
    {
        const IDataType* currentType = dataType;
        auto current = parseNode;

        while (true)
        {
            if (current->NodeType() == NodeType::Identifier)
                return TryCompileConstant(current, constant, currentType, dataType);

            if (current->NodeType() != NodeType::Dot)
            {
                PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                return std::nullopt;
            }

            if (const auto lhs = parseNode->GetChild(static_cast<int>(ChildCode::LHS)); lhs->NodeType() == NodeType::Identifier)
            {
                const auto characteristic = currentType->FindCharacteristic(*lhs->Token().Value<string>());
                if (characteristic == nullptr)
                {
                    PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                    return std::nullopt;
                }

                currentType = characteristic->CreationType();
                current = parseNode->GetChild(static_cast<int>(ChildCode::RHS));

                continue;
            }

            PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
            return std::nullopt;
        }
    }

    std::optional<CompilationResult> CompileExpression(const IParseNode* const parseNode, ICharacteristic* const constant, const IUserDefinedType* const dataType)
    {
        switch (parseNode->NodeType())
        {
            case NodeType::Dot:
                    return CompileEntity(parseNode, constant, dataType);
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
                                PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
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

                    PushException(new LogException("No built in cast not found", parseNode->Token().Index(), dataType->Parent()));
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
                        PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    const auto overload = operand->creationType->FindBuiltInOverload(operation);

                    if (overload == nullptr)
                    {
                        PushException(new OverloadNotFoundException(operation, parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *operand });
                }
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
                        PushException(new LogException(std::format("Cannot perform built int operation between types: {} and: {}", lhs->creationType->FullName(), rhs->creationType->FullName()), parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    const auto overload = lhs->creationType->FindBuiltInOverload(parseNode->Token().Kind());

                    if (overload == nullptr)
                    {
                        PushException(new OverloadNotFoundException(parseNode->Token().Kind(), parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *lhs, *rhs });
                }
            default:
                PushException(new ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                return std::nullopt;
        }
    }

    const IContextNode* ConstantCompile(ICharacteristic* const characteristic, const IUserDefinedType* dataType)
    {
        const auto result = CompileExpression(characteristic->ParseNode(), characteristic, dataType);
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
                return new StringConstant(std::get<std::string>(result->data));
            default:
                return nullptr;
        }
    }
}
