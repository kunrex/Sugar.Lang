#include "constant_binder.h"

#include <format>

#include "binder_extensions.h"

#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/short.h"
#include "../../Structure/Wrappers/Value/double.h"
#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Value/integer.h"
#include "../../Structure/Wrappers/Value/character.h"
#include "../../Structure/Wrappers/Reference/string.h"

#include "../../Structure/Compilation/compilation_result.h"

#include "../../Structure/Context/invalid_context.h"
#include "../../Structure/Context/Constants/float_constant.h"
#include "../../Structure/Context/Constants/integer_constant.h"
#include "../../Structure/Context/Constants/string_constant.h"
#include "../../Structure/Context/Entities/Functions/creation_context.h"

#include "../../Structure/Core/Interfaces/DataTypes/i_primitive_type.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_collection_type.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/Local/constant_expected_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/overload_not_found_exception.h"

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
    const IContextNode* VariableCompile(const IParseNode* parseNode, ICharacteristic* characteristic, const IUserDefinedType* dataType);

    const IPrimitiveType* BindPrimitiveType(const IParseNode* const node)
    {
        switch (node->Token().Kind())
        {
            case SyntaxKind::Short:
                return Short::Instance();
            case SyntaxKind::Int:
                return Integer::Instance();
            case SyntaxKind::Long:
                return Long::Instance();
            case SyntaxKind::Float:
                return Float::Instance();
            case SyntaxKind::Double:
                return Double::Instance();
            case SyntaxKind::String:
                return String::Instance();
            case SyntaxKind::Character:
                return Character::Instance();
            default:
                return Boolean::Instance();
        }
    }

    std::optional<CompilationResult> AsCompilationResult(const ICharacteristic* const constant)
    {
        switch (constant->CreationType()->Type())
        {
            case TypeKind::Short:
                return CompilationResult(Short::Instance(), *reinterpret_cast<const short*>(constant->Context()->Metadata()));
            case TypeKind::Int:
            case TypeKind::EnumField:
                return CompilationResult(Integer::Instance(), *reinterpret_cast<const int*>(constant->Context()->Metadata()));
            case TypeKind::Long:
                return CompilationResult(Long::Instance(), *reinterpret_cast<const long*>(constant->Context()->Metadata()));
            case TypeKind::Float:
                return CompilationResult(Float::Instance(), *reinterpret_cast<const float*>(constant->Context()->Metadata()));
            case TypeKind::Double:
                return CompilationResult(Double::Instance(), *reinterpret_cast<const double*>(constant->Context()->Metadata()));
            case TypeKind::Boolean:
                return CompilationResult(Boolean::Instance(), *reinterpret_cast<const bool*>(constant->Context()->Metadata()));
            case TypeKind::Character:
                return CompilationResult(Character::Instance(), *reinterpret_cast<const char*>(constant->Context()->Metadata()));
            case TypeKind::String:
                return CompilationResult(String::Instance(), *reinterpret_cast<const std::string*>(constant->Context()->Metadata()));
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
                        return std::nullopt;

                    if (constant->HasDependant(characteristic))
                    {
                        ExceptionManager::PushException(LogException(std::format("Cyclic dependency between: {} and: {}", constant->FullName(), characteristic->FullName()), identifierNode->Token().Index(), dataType->Parent()));
                        constant->IncrementDependencyCount();

                        return std::nullopt;
                    }

                    characteristic->PushDependant(constant);
                }
                break;
            default:
                ExceptionManager::PushException(ConstantNotFoundException(identifierNode->Token().Index(), dataType->Parent()));
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
                ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                return std::nullopt;
            }

            if (const auto lhs = parseNode->GetChild(static_cast<int>(ChildCode::LHS)); lhs->NodeType() == NodeType::Identifier)
            {
                const auto characteristic = currentType->FindCharacteristic(*lhs->Token().Value<std::string>());
                if (characteristic == nullptr)
                {
                    ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                    return std::nullopt;
                }

                currentType = characteristic->CreationType();
                current = parseNode->GetChild(static_cast<int>(ChildCode::RHS));

                continue;
            }

            ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
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
                    switch (const auto& token = parseNode->Token(); static_cast<TypeKind>(token.Metadata()))
                    {
                        case TypeKind::Short:
                            return CompilationResult(Short::Instance(), static_cast<short>(*token.Value<long>()));
                        case TypeKind::Int:
                            return CompilationResult(Integer::Instance(), static_cast<int>(*token.Value<long>()));
                        case TypeKind::Long:
                            return CompilationResult(Long::Instance(), *token.Value<long>());
                        case TypeKind::Character:
                            return CompilationResult(Character::Instance(), static_cast<char>(*token.Value<long>()));
                        case TypeKind::Boolean:
                            return CompilationResult(Boolean::Instance(), static_cast<bool>(*token.Value<long>()));
                        case TypeKind::Float:
                            return CompilationResult(Float::Instance(), static_cast<float>(*token.Value<double>()));
                        case TypeKind::Double:
                            return CompilationResult(Double::Instance(), *token.Value<double>());
                        case TypeKind::String:
                            return CompilationResult(String::Instance(), *token.Value<std::string>());
                        default:
                            ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                            return std::nullopt;
                    }
                }
            case NodeType::Identifier:
                return TryCompileConstant(parseNode, constant, dataType, dataType);
            case NodeType::Cast:
                {
                    const auto operand = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::LHS)), constant, dataType);
                    if (!operand)
                        return std::nullopt;

                    const auto type = BindPrimitiveType(parseNode->GetChild(static_cast<int>(ChildCode::RHS)));

                    if (const auto cast = operand->creationType->FindBuiltInCast(type, operand->creationType); cast != nullptr)
                        return cast->StaticCompile(*operand);

                    ExceptionManager::PushException(LogException("No built in cast not found", parseNode->Token().Index(), dataType->Parent()));
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
                        ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    const auto overload = operand->creationType->FindBuiltInOverload(operation);

                    if (overload == nullptr)
                    {
                        ExceptionManager::PushException(OverloadNotFoundException(operation, parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *operand });
                }
            case NodeType::Binary:
                {
                    const auto lhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::LHS)), constant, dataType);
                    const auto rhs = CompileExpression(parseNode->GetChild(static_cast<int>(ChildCode::RHS)), constant, dataType);
                    if (!lhs || !rhs)
                        return std::nullopt;

                    if (lhs->creationType != rhs->creationType)
                    {
                        ExceptionManager::PushException(LogException(std::format("Cannot perform built int operation between types: {} and: {}", lhs->creationType->FullName(), rhs->creationType->FullName()), parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    const auto overload = lhs->creationType->FindBuiltInOverload(parseNode->Token().Kind());

                    if (overload == nullptr)
                    {
                        ExceptionManager::PushException(OverloadNotFoundException(parseNode->Token().Kind(), parseNode->Token().Index(), dataType->Parent()));
                        return std::nullopt;
                    }

                    return overload->StaticCompile({ *lhs, *rhs });
                }
            default:
                ExceptionManager::PushException(ConstantNotFoundException(parseNode->Token().Index(), dataType->Parent()));
                return std::nullopt;
        }
    }

    const IContextNode* ConstantCompile(const IParseNode* const parseNode, ICharacteristic* const characteristic, const IUserDefinedType* const dataType)
    {
        const auto result = CompileExpression(parseNode, characteristic, dataType);
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

    const IContextNode* ConstantCompile(ICharacteristic* const characteristic, const IUserDefinedType* dataType)
    {
        return ConstantCompile(characteristic->ParseNode(), characteristic, dataType);
    }

    const IContextNode* CompileConstructor(const IParseNode* const constructorCallNode, ICharacteristic* const characteristic, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto creationType = BindDataType(constructorCallNode->GetChild(0), source);
        if (creationType != characteristic->CreationType())
            return new InvalidContext();

        std::vector<const IContextNode*> arguments;
        std::vector<const IDataType*> argumentTypes;

        arguments.reserve(constructorCallNode->ChildCount() - 1);
        argumentTypes.reserve(constructorCallNode->ChildCount() - 1);

        bool flag = false;
        for (int i = 1; i < constructorCallNode->ChildCount(); i++)
        {
            if (const auto context = VariableCompile(constructorCallNode->GetChild(i), characteristic, dataType); context != nullptr)
            {
                arguments.push_back(context);
                argumentTypes.push_back(context->CreationType());
            }
            else
            {
                flag = true;
                const auto value = new InvalidContext();

                arguments.push_back(value);
                argumentTypes.push_back(value->CreationType());
            }
        }

        if (flag)
        {
            for (const auto argument : arguments)
                delete argument;

            return nullptr;
        }

        if (const auto constructor = creationType->FindConstructor(argumentTypes); constructor != nullptr)
        {
            const auto context = new CreationContext(constructor);
            for (const auto argument: arguments)
                context->AddChild(argument);

            return context;
        }

        ExceptionManager::PushException(LogException(std::format("No appropriate constructor for: `{}` was found", creationType->FullName()), constructorCallNode->Token().Index(), source));
        return new InvalidContext();
    }

    const IContextNode* CompileCollectionConstructor(const IParseNode* const constructorCallNode, ICharacteristic* const characteristic, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto creationType = BindDataType(constructorCallNode->GetChild(0), source);
        if (creationType != characteristic->CreationType())
            return new InvalidContext();

        const auto collectionType = dynamic_cast<const ICollectionType*>(creationType);
        const auto genericType = collectionType->GenericType();

        std::vector<const IContextNode*> arguments;
        arguments.reserve(constructorCallNode->ChildCount() - 1);

        bool flag = false;
        for (int i = 1; i < constructorCallNode->ChildCount(); i++)
        {
            const auto child = constructorCallNode->GetChild(i);

            if (const auto context = VariableCompile(child, characteristic, dataType); context != nullptr)
            {
                if (context->CreationType() != genericType)
                    ExceptionManager::PushException(LogException(std::format("Expected argument of type: {}", genericType->FullName()), child->Token().Index(), source));

                arguments.push_back(context);
            }
            else
            {
                flag = true;
                arguments.push_back(new InvalidContext());
            }
        }

        if (flag)
        {
            for (const auto argument : arguments)
                delete argument;

            return nullptr;
        }

        const auto context = new CollectionCreationContext(collectionType);
        for (const auto argument : arguments)
            context->AddChild(argument);

        return context;
    }

    const IContextNode* VariableCompile(const IParseNode* const parseNode, ICharacteristic* const characteristic, const IUserDefinedType* dataType)
    {
        switch (parseNode->NodeType())
        {
            case NodeType::ConstructorCall:
                return CompileConstructor(parseNode, characteristic, dataType);
            case NodeType::CollectionConstructorCall:
                return CompileCollectionConstructor(parseNode, characteristic, dataType);
            default:
                return ConstantCompile(parseNode, characteristic, dataType);
        }
    }

    const IContextNode* VariableCompile(ICharacteristic* const characteristic, const IUserDefinedType* const dataType)
    {
        return VariableCompile(characteristic->ParseNode(), characteristic, dataType);
    }
}
