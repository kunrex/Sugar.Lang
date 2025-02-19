#include "local_binder.h"

#include <format>

#include "binder_extensions.h"
#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/variable_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Parsing/ParseNodes/Conditions/condition_node.h"
#include "../../../Parsing/ParseNodes/Conditions/else_node.h"
#include "../../../Parsing/ParseNodes/Conditions/if_node.h"
#include "../../../Parsing/ParseNodes/Constants/constant_node.h"
#include "../../../Parsing/ParseNodes/Expressions/cast_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/dot_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/indexer_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Binary/binary_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Unary/unary_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/function_call_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/format_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/funcref_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/invoke_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/print_node.h"
#include "../../../Parsing/ParseNodes/Groups/if_chain_node.h"
#include "../../../Parsing/ParseNodes/Groups/scope_node.h"
#include "../../../Parsing/ParseNodes/Loops/do_while_node.h"
#include "../../../Parsing/ParseNodes/Loops/for_loop_node.h"
#include "../../../Parsing/ParseNodes/Loops/while_node.h"
#include "../../../Parsing/ParseNodes/Statements/declaration_node.h"
#include "../../../Parsing/ParseNodes/Statements/expression_statement_node.h"
#include "../../../Parsing/ParseNodes/Statements/initialisation_node.h"
#include "../../../Parsing/ParseNodes/Statements/Control/return_node.h"
#include "../../Structure/Nodes/Context/invalid_context.h"
#include "../../Structure/Nodes/Context/static_reference_context.h"
#include "../../Structure/Nodes/Context/this_context.h"
#include "../../Structure/Nodes/Context/Casts/box_cast_expression.h"
#include "../../Structure/Nodes/Context/Casts/built_in_cast_expression.h"
#include "../../Structure/Nodes/Context/Casts/cast_class_expression.h"
#include "../../Structure/Nodes/Context/Casts/defined_cast_expression.h"
#include "../../Structure/Nodes/Context/Casts/invalid_cast_node.h"
#include "../../Structure/Nodes/Context/Casts/unbox_cast_expression.h"
#include "../../Structure/Nodes/Context/Constants/float_constant.h"
#include "../../Structure/Nodes/Context/Constants/integer_constant.h"
#include "../../Structure/Nodes/Context/Constants/null_constant.h"
#include "../../Structure/Nodes/Context/Constants/string_constant.h"
#include "../../Structure/Nodes/Context/Control/branch.h"
#include "../../Structure/Nodes/Context/Control/branch_condition.h"
#include "../../Structure/Nodes/Context/Control/return.h"
#include "../../Structure/Nodes/Context/Entities/Functions/format.h"
#include "../../Structure/Nodes/Context/Entities/Functions/function_context.h"
#include "../../Structure/Nodes/Context/Entities/Functions/input.h"
#include "../../Structure/Nodes/Context/Entities/Functions/invalid_function_context.h"
#include "../../Structure/Nodes/Context/Entities/Functions/print.h"
#include "../../Structure/Nodes/Context/Entities/Functions/println.h"
#include "../../Structure/Nodes/Context/Entities/References/argument_context.h"
#include "../../Structure/Nodes/Context/Entities/References/field_context.h"
#include "../../Structure/Nodes/Context/Entities/References/local_variable_context.h"
#include "../../Structure/Nodes/Context/Entities/References/property_context.h"
#include "../../Structure/Nodes/Context/Expressions/built_in_binary_expression.h"
#include "../../Structure/Nodes/Context/Expressions/built_in_indexer_expression.h"
#include "../../Structure/Nodes/Context/Expressions/built_in_unary_expression.h"
#include "../../Structure/Nodes/Context/Expressions/dot_expression.h"
#include "../../Structure/Nodes/Context/Expressions/defined_binary_expression.h"
#include "../../Structure/Nodes/Context/Expressions/defined_indexer_expression.h"
#include "../../Structure/Nodes/Context/Expressions/defined_unary_expression.h"
#include "../../Structure/Nodes/Context/Expressions/invalid_binary_expression.h"
#include "../../Structure/Nodes/Context/Expressions/invalid_indexer_expression.h"
#include "../../Structure/Nodes/Context/Expressions/invalid_unary_expression.h"
#include "../../Structure/Nodes/Global/Properties/property.h"
#include "../../Structure/Nodes/Global/UserDefined/void_function.h"
#include "../../Structure/Nodes/Local/Scopes/scope.h"
#include "../../Structure/Nodes/Local/Variables/local_variable.h"
#include "../../Structure/Wrappers/Generic/action.h"
#include "../../Structure/Wrappers/Generic/func.h"
#include "../../Structure/Wrappers/Reference/exception.h"
#include "../../Structure/Wrappers/Reference/object.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Value/character.h"
#include "../../Structure/Wrappers/Value/double.h"
#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/integer.h"
#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/short.h"

using namespace Services;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Loops;
using namespace ParseNodes::Values;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Constants;
using namespace ParseNodes::Conditions;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;
using namespace ParseNodes::Functions::Calling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Creation;

constexpr std::string_view CHECK = "C";

constexpr std::string_view LOOP = "L";

constexpr std::string_view BODY = "B";
constexpr std::string_view POST = "P";
constexpr std::string_view END = "E";

constexpr std::string_view SCOPE = "S";
constexpr std::string_view CONTINUATION = "T";

namespace Analysis::Creation::Binding
{
    const ContextNode* BindEntity(const ParseNode* entity, const ContextNode* context, Scoped* scoped, const Scope* scope, const DataType* dataType);

    const ContextNode* BindExpression(const ParseNode* expression, Scoped* scoped, const Scope* scope, const DataType* dataType);

    bool VariableExists(const IdentifierNode* identifier, const Scoped* const scoped, const Scope* scope)
    {
        const auto value = identifier->Value();

        if (const auto local = scope->GetVariable(value); local > 0)
            return true;

        if (scoped->ContainsArgument(value))
            return true;

        return false;
    }

    void BindLocalDeclaration(const DeclarationNode* declaration, const Scoped* const scoped, Scope* const scope, const DataType* dataType)
    {
        if (const auto identifierNode = declaration->Name(); VariableExists(identifierNode, scoped, scope))
        {
            ExceptionManager::Instance().AddChild(new DuplicateVariableDefinitionException(identifierNode->Value(), identifierNode->Token().Index(), dataType->Parent()));
            return;
        }

        const auto describer = FromNode(declaration->Describer());
        const auto identifier = declaration->Name()->Value();

        switch (const auto typeNode = declaration->Type(); typeNode->NodeType())
        {
            case NodeType::VoidType:
            case NodeType::AnonymousType:
                ExceptionManager::Instance().AddChild(new DuplicateVariableDefinitionException(identifier, declaration->Name()->Token().Index(), dataType->Parent()));
                break;
            default:
                {
                    const auto type = BindDataType(typeNode, dataType->Parent());
                    const auto variable = new LocalVariable(identifier, describer, type);
                    if (!variable->ValidateDescriber(Describer::None))
                        ExceptionManager::Instance().AddChild(new InvalidDescriberException(describer, Describer::None, dataType->Parent()));

                    scope->AddVariable(variable);
                }
                break;
        }
    }

    const ContextNode* BindCast(const CastDefinition* const definition, const ContextNode* operand)
    {
        if (definition->MemberType() == MemberType::BuiltInCast)
            return new BuiltInCastExpression(definition, operand);

        return new DefinedCastExpression(definition, operand);
    }

    const ContextNode* BindCast(const ContextNode* const operand, const DataType* const type, const CastDefinition* const operandCast, const CastDefinition* const typeCast)
    {
        const auto operandValid = operandCast != nullptr;
        const auto typeValid = typeCast != nullptr;

        if (operandValid)
        {
            if (typeValid)
            {
                //exception
                 return new InvalidCastNode(type, operand);
            }

            return BindCast(operandCast, operand);
        }
        if (typeValid)
            return BindCast(typeCast, operand);

        //exception
        return new InvalidCastNode(type, operand);
    }

    void BindLocalInitialisation(const InitialisationNode* const initialisation, Scoped* const scoped, Scope* const scope, const DataType* const dataType)
    {
        if (const auto identifierNode = initialisation->Name(); VariableExists(identifierNode, scoped, scope))
        {
            ExceptionManager::Instance().AddChild(new DuplicateVariableDefinitionException(identifierNode->Value(), identifierNode->Token().Index(), dataType->Parent()));
            return;
        }

        const auto describer = FromNode(initialisation->Describer());
        const auto identifier = initialisation->Name()->Value();

        switch (const auto typeNode = initialisation->Type(); typeNode->NodeType())
        {
            case NodeType::VoidType:
                ExceptionManager::Instance().AddChild(new DuplicateVariableDefinitionException(identifier, initialisation->Name()->Token().Index(), dataType->Parent()));
                break;
            case NodeType::AnonymousType:
                {
                    const auto context = BindExpression(initialisation->Value(), scoped, scope, dataType);
                    const auto variable = new LocalVariable(identifier, describer, context->CreationType());

                    scope->AddChild(context);

                    if (!variable->ValidateDescriber(Describer::None))
                        ExceptionManager::Instance().AddChild(new InvalidDescriberException(describer, Describer::None, dataType->Parent()));

                    scope->AddVariable(variable);
                }
                break;
            default:
                {
                    const auto type = BindDataType(typeNode, dataType->Parent());
                    const auto variable = new LocalVariable(identifier, describer, type);

                    if (const auto value = BindExpression(initialisation->Value(), scoped, scope, dataType); value->CreationType() != type)
                    {
                        if (type == &Object::Instance())
                        {
                            if (value->CreationType()->MemberType() == MemberType::Struct)
                                scope->AddChild(new BoxCastExpression(value));
                            else
                                scope->AddChild(value);
                        }
                        else
                        {
                            const auto valueCast = value->CreationType()->FindImplicitCast(type, value->CreationType());
                            const auto resultCast = type->FindImplicitCast(type, value->CreationType());

                            scope->AddChild(BindCast(value, type, valueCast, resultCast));
                        }
                    }
                    else
                        scope->AddChild(value);

                    if (!variable->ValidateDescriber(Describer::None))
                        ExceptionManager::Instance().AddChild(new InvalidDescriberException(describer, Describer::None, dataType->Parent()));

                    scope->AddVariable(variable);
                }
                break;
        }
    }

    const ContextNode* BindConstant(const ConstantNode* constant)
    {
        switch (constant->ConstantType())
        {
            case TypeKind::Short:
                return new ShortConstant(static_cast<short>(constant->Value<long>().value()));
            case TypeKind::Int:
                return new IntegerConstant(static_cast<int>(constant->Value<long>().value()));
            case TypeKind::Long:
                return new LongConstant(constant->Value<long>().value());
            case TypeKind::Float:
                return new FloatConstant(static_cast<float>(constant->Value<double>().value()));
            case TypeKind::Double:
                return new DoubleConstant(constant->Value<double>().value());
            case TypeKind::Character:
                return new CharacterConstant(static_cast<char>(constant->Value<long>().value()));
            case TypeKind::Boolean:
                {
                    if (static_cast<bool>(constant->Value<long>().value()))
                        return new TrueConstant();

                    return new FalseConstant();
                }
            case TypeKind::String:
                return new StringConstant(constant->Value<std::string>().value());
            case TypeKind::Object:
                return new NullConstant();
            default:
                return new InvalidContext();
        }
    }

    const ContextNode* BindIdentifier(const IdentifierNode* identifier, const Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        const auto value = identifier->Value();

        if (const auto local = scope->GetVariable(value); local > 0)
        {
            const auto variable = scoped->VariableAt(local);
            return new LocalVariableContext(variable, local - scoped->ArgumentCount());
        }

        if (const auto argument = scoped->GetArgument(value); argument > 0)
        {
            const auto variable = scoped->VariableAt(argument);
            return new ArgumentContext(variable, argument);
        }

        if (const auto characteristic = dataType->FindCharacteristic(value); characteristic != nullptr)
        {
            if (scoped->CheckDescriber(Describer::Static) && !characteristic->CheckDescriber(Describer::Static))
            {
                //exception
            }

            switch (characteristic->MemberType())
            {
                case MemberType::Field:
                    return new FieldContext(characteristic);
                case MemberType::Property:
                    return new PropertyContext(dynamic_cast<const Property*>(characteristic));
                default:
                    break;
            }
        }

        return nullptr;
    }

    void BindArgumentContexts(const NodeCollection<ParseNode>* const functionNode, std::vector<const ContextNode*>& arguments, std::vector<const DataType*>& argumentTypes, Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        for (int i = 0; i < functionNode->ChildCount(); i++)
        {
            const auto current = functionNode->GetChild(i);
            const auto currentContext = BindExpression(current, scoped, scope, dataType);

            arguments.push_back(currentContext);
            argumentTypes.push_back(currentContext->CreationType());
        }
    }

    const ContextNode* CreateFunctionContext(const FunctionDefinition* function, const std::vector<const ContextNode*>& arguments)
    {
        const auto functionContext = new FunctionContext(function, false);
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        return functionContext;
    }

    const ContextNode* CreateStaticFunctionContext(const FunctionDefinition* function, const std::vector<const ContextNode*>& arguments)
    {
        const auto functionContext = new FunctionContext(function, true);
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        return functionContext;
    }

    const ContextNode* CreateInvalidFunctionContext(const std::vector<const ContextNode*>& arguments)
    {
        const auto functionContext = new InvalidFunctionContext();
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        return functionContext;
    }

    const ContextNode* BindFunctionCall(const FunctionCallNode* functionNode, Scoped* const scoped, const Scope* scope, const DataType* const dataType)
    {
        const auto identifier = functionNode->Identifier()->Value();

        std::vector<const ContextNode*> arguments;
        std::vector<const DataType*> argumentTypes;
        BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

        if (const auto function = dataType->FindFunction(identifier, argumentTypes); function != nullptr)
        {
            if (scoped->CheckDescriber(Describer::Static) && !function->CheckDescriber(Describer::Static))
            {
                //exception
            }

            if (function->CheckDescriber(Describer::Static))
                return CreateStaticFunctionContext(function, arguments);

            return CreateFunctionContext(function, arguments);
        }

        //exception
        return CreateInvalidFunctionContext(arguments);
    }

    const ContextNode* BindDotLHS(const ParseNode* lhs, Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        switch (lhs->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto identifier = dynamic_cast<const IdentifierNode*>(lhs);

                    if (const auto characteristic = BindIdentifier(identifier, scoped, scope, dataType); characteristic != nullptr)
                        return characteristic;

                    if (const auto type = dataType->Parent()->GetReference(identifier->Value()); type != nullptr)
                        return new StaticReferenceContext(type);
                }
                break;
            case NodeType::FunctionCall:
                return BindFunctionCall(dynamic_cast<const FunctionCallNode*>(lhs), scoped, scope, dataType);
            case NodeType::FuncType:
            case NodeType::ListType:
            case NodeType::TupleType:
            case NodeType::ArrayType:
            case NodeType::ActionType:
            case NodeType::BuiltInType:
            case NodeType::NullableType:
            case NodeType::DictionaryType:
                return new StaticReferenceContext(BindDataType(lhs, dataType->Parent()));
            case NodeType::This:
                return new ThisContext(dataType);
            case NodeType::Constant:
                return BindConstant(dynamic_cast<const ConstantNode*>(lhs));
            default:
                break;
        }

        //exception
        return new InvalidContext();
    }

    const ContextNode* BindIndexerExpression(const IndexerExpressionNode* const indexerNode, const ContextNode* operand, Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        std::vector<const ContextNode*> arguments;
        std::vector<const DataType*> argumentTypes;
        BindArgumentContexts(indexerNode, arguments, argumentTypes, scoped, scope, dataType);

        if (const auto indexer = operand->CreationType()->FindIndexer(argumentTypes); indexer != nullptr)
        {
            if (dataType != operand->CreationType() && !indexer->CheckDescriber(Describer::Public))
            {
                //exception
            }

            if (indexer->MemberType() == MemberType::BuiltInIndexer)
            {
                const auto indexerContext = new BuiltInIndexerExpression(indexer, operand);
                for (const auto argument: arguments)
                    indexerContext->AddChild(argument);

                return indexerContext;
            }
            {
                const auto indexerContext = new DefinedIndexerExpression(indexer, operand);
                for (const auto argument: arguments)
                    indexerContext->AddChild(argument);

                return indexerContext;
            }
        }

        //exception
        const auto invalidIndexer = new InvalidIndexerExpression(operand);
        for (const auto argument: arguments)
            invalidIndexer->AddChild(argument);

        return invalidIndexer;
    }

    const ContextNode* BindStaticDotRHS(const ParseNode* rhs, const ContextNode* context, Scoped* scoped, const Scope* scope, const DataType* const dataType)
    {
        switch (rhs->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto dot = dynamic_cast<const DotExpressionNode*>(rhs);

                    const auto lhsContext = BindStaticDotRHS(dot->LHS(), context, scoped, scope, dataType);
                    const auto rhsContext = BindEntity(dot->RHS(), lhsContext, scoped, scope, dataType);

                    return new DotExpression(context, new DotExpression(lhsContext, rhsContext));
                }
            case NodeType::Identifier:
                {
                    const auto identifier = dynamic_cast<const IdentifierNode*>(rhs);

                    if (const auto characteristic = context->CreationType()->FindCharacteristic(identifier->Value()); characteristic != nullptr)
                    {
                        if (!characteristic->CheckDescriber(Describer::Static))
                        {
                            //exception
                        }
                        if (dataType != context->CreationType() && !characteristic->CheckDescriber(Describer::Public))
                        {
                            //exception
                        }

                        switch (characteristic->MemberType())
                        {
                            case MemberType::Field:
                                return new DotExpression(context, new FieldContext(characteristic));
                            case MemberType::Property:
                                return new DotExpression(context, new PropertyContext(dynamic_cast<const Property*>(characteristic)));
                            default:
                                break;
                        }
                    }
                }
                break;
            case NodeType::FunctionCall:
                {
                    const auto functionNode = dynamic_cast<const FunctionCallNode*>(rhs);

                    const auto identifier = functionNode->Identifier()->Value();

                    std::vector<const ContextNode*> arguments;
                    std::vector<const DataType*> argumentTypes;
                    BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto function = context->CreationType()->FindFunction(identifier, argumentTypes); function != nullptr)
                    {
                        if (!function->CheckDescriber(Describer::Static))
                        {
                            //exception
                        }
                        if (dataType != context->CreationType() && !function->CheckDescriber(Describer::Public))
                        {
                            //exception
                        }

                        return new DotExpression(context, CreateStaticFunctionContext(function, arguments));
                    }

                    //exception
                    return new DotExpression(context, CreateInvalidFunctionContext(arguments));
                }
            default:
                break;
        }


        //exception
        return new DotExpression(context, new InvalidContext());
    }

    const ContextNode* BindEntity(const ParseNode* entity, const ContextNode* const context, Scoped* const scoped, const Scope* scope, const DataType* const dataType)
    {
        switch (entity->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto dot = dynamic_cast<const DotExpressionNode*>(entity);

                    const auto lhsContext = BindEntity(dot->LHS(), context, scoped, scope, dataType);
                    const auto rhsContext = BindEntity(dot->RHS(), lhsContext, scoped, scope, dataType);

                    return new DotExpression(context, new DotExpression(lhsContext, rhsContext));
                }
            case NodeType::Identifier:
                {
                    const auto identifier = dynamic_cast<const IdentifierNode*>(entity);
                    if (const auto characteristic = context->CreationType()->FindCharacteristic(identifier->Value()); characteristic != nullptr)
                    {
                        if (dataType != context->CreationType() && !characteristic->CheckDescriber(Describer::Public))
                        {
                            //exception
                        }

                        const auto field = new FieldContext(characteristic);
                        return new DotExpression(context, field);
                    }
                }
                break;
            case NodeType::FunctionCall:
                {
                    const auto functionNode = dynamic_cast<const FunctionCallNode*>(entity);

                    const auto identifier = functionNode->Identifier()->Value();

                    std::vector<const ContextNode*> arguments;
                    std::vector<const DataType*> argumentTypes;
                    BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto function = context->CreationType()->FindFunction(identifier, argumentTypes); function != nullptr)
                    {
                        if (dataType != context->CreationType() && !function->CheckDescriber(Describer::Public))
                        {
                            //exception
                        }

                        if (function->CheckDescriber(Describer::Static))
                            return new DotExpression(context, CreateStaticFunctionContext(function, arguments));

                        return new DotExpression(context, CreateFunctionContext(function, arguments));
                    }

                    //exception
                    return new DotExpression(context, CreateInvalidFunctionContext(arguments));
                }
            case NodeType::Indexer:
                {
                    const auto indexerNode = dynamic_cast<const IndexerExpressionNode*>(entity);
                    const auto operand = BindEntity(indexerNode->Operand(), context, scoped, scope, dataType);

                    return new DotExpression(context, BindIndexerExpression(indexerNode, operand, scoped, scope, dataType));
                }
            default:
                break;
        }

        //exception
        return new DotExpression(context, new InvalidContext());
    }

    const ContextNode* BindPrint(const ContextNode* const operand, const bool ln)
    {
        if (operand->CreationType() == &Short::Instance())
            return new PrintShort(operand, ln);
        if (operand->CreationType() == &Integer::Instance())
            return new PrintInt(operand, ln);
        if (operand->CreationType() == &Long::Instance())
            return new PrintLong(operand, ln);
        if (operand->CreationType() == &Float::Instance())
            return new PrintFloat(operand, ln);
        if (operand->CreationType() == &Double::Instance())
            return new PrintDouble(operand, ln);
        if (operand->CreationType() == &Character::Instance())
            return new PrintChar(operand, ln);
        if (operand->CreationType() == &Boolean::Instance())
            return new PrintBool(operand, ln);
        if (operand->CreationType() == &String::Instance())
            return new PrintString(operand, ln);

        return new PrintObject(operand, ln);
    }

    const ContextNode* BindEntity(const ParseNode* entity, Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        switch (entity->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto dot = dynamic_cast<const DotExpressionNode*>(entity);
                    const auto lhs = BindDotLHS(dot->LHS(), scoped, scope, dataType);

                    if (lhs->MemberType() == MemberType::StaticReferenceContext)
                        return BindStaticDotRHS(dot->RHS(), lhs, scoped, scope, dataType);

                    return BindEntity(dot->RHS(), lhs, scoped, scope, dataType);
                }
            case NodeType::Constant:
                return BindConstant(dynamic_cast<const ConstantNode*>(entity));
            case NodeType::Identifier:
                {
                    const auto identifier = dynamic_cast<const IdentifierNode*>(entity);

                    if (const auto character = BindIdentifier(identifier, scoped, scope, dataType); character != nullptr)
                        return character;
                }
                break;
            case NodeType::FunctionCall:
                return BindFunctionCall(dynamic_cast<const FunctionCallNode*>(entity), scoped, scope, dataType);
            case NodeType::Indexer:
                {
                    const auto indexerNode = dynamic_cast<const IndexerExpressionNode*>(entity);
                    const auto operand = BindEntity(indexerNode->Operand(), scoped, scope, dataType);

                    return BindIndexerExpression(indexerNode, operand, scoped, scope, dataType);
                }
            case NodeType::Input:
                return new Input();
            case NodeType::Print:
                {
                    if (const auto printNode = dynamic_cast<const PrintNode*>(entity); printNode->ChildCount() > 0)
                    {
                        const auto arg = printNode->GetChild(0);
                        const auto context = BindExpression(arg, scoped, scope, dataType);
                        return BindPrint(context, false);
                    }

                    return new Print(false);
                }
                break;
            case NodeType::Println:
                {
                    if (const auto printlnNode = dynamic_cast<const PrintlnNode*>(entity); printlnNode->ChildCount() > 0)
                    {
                        const auto arg = printlnNode->GetChild(0);
                        const auto context = BindExpression(arg, scoped, scope, dataType);
                        return BindPrint(context, true);
                    }

                    return new Print(true);
                }
                break;
            case NodeType::Format:
                {
                    const auto formatNode = dynamic_cast<const FormatNode*>(entity);

                    std::vector<const ContextNode*> arguments;
                    std::vector<const DataType*> argumentTypes;
                    BindArgumentContexts(formatNode, arguments, argumentTypes, scoped, scope, dataType);

                    const auto format = new Format();
                    for (const auto argument: arguments)
                        format->AddChild(argument);

                    return format;
                }
            case NodeType::Invoke:
                {
                    const auto invokeNode = dynamic_cast<const InvokeNode*>(entity);

                    std::vector<const ContextNode*> arguments;
                    for (const auto argument: *invokeNode)
                        arguments.push_back(BindExpression(argument, scoped, scope, dataType));

                    if (const auto delegate = arguments[0]; delegate->CreationType()->Name() != "Action")
                    {
                        const auto action = dynamic_cast<const Action*>(delegate->CreationType());

                        bool invalid = false;
                        for (int i = 0; i < arguments.size(); i++)
                        {
                            if (i >= action->TypeCount() || arguments[i + 1]->CreationType() != action->TypeAt(i))
                                invalid = true;
                        }

                        if (!invalid)
                        {
                            const auto actionContext = new AcionInvoke(delegate);
                            for (int i = 1; i < arguments.size(); i++)
                                actionContext->AddChild(arguments[i]);

                            return actionContext;
                        }
                    }
                    else if (delegate->CreationType()->Name() != "Func")
                    {
                        const auto func = dynamic_cast<const Func*>(delegate->CreationType());

                        bool invalid = false;
                        for (int i = 0; i < arguments.size(); i++)
                        {
                            if (i >= func->TypeCount() || arguments[i + 1]->CreationType() != func->TypeAt(i))
                                invalid = true;
                        }

                        if (!invalid)
                        {
                            const auto actionContext = new FuncInvoke(delegate);
                            for (int i = 1; i < arguments.size(); i++)
                                actionContext->AddChild(arguments[i]);

                            return actionContext;
                        }
                    }

                    const auto invalidInvoke = new InvalidInvoke();
                    for (const auto argument: arguments)
                        invalidInvoke->AddChild(argument);

                    return invalidInvoke;
                }
                break;
            case NodeType::FuncRef:
                {
                    const auto funcRefNode = dynamic_cast<const FuncRefNode*>(entity);
                    const auto objectNode = funcRefNode->GetChild(0);

                    const auto functionCallNode = funcRefNode->GetChild(1);
                    if (functionCallNode->NodeType() != NodeType::Identifier)
                    {
                        //exception
                        return new InvalidContext();
                    }

                    const auto identifier = dynamic_cast<const IdentifierNode*>(functionCallNode);

                    bool flag = false;
                    const ContextNode* objectContext = nullptr;
                    if (objectNode->NodeType() == NodeType::Identifier)
                    {
                        const auto objectIdentifier = dynamic_cast<const IdentifierNode*>(objectNode);

                        if (const auto type = BindDataType(objectIdentifier, dataType->Parent()); type != nullptr)
                        {
                            flag = true;
                            objectContext = new StaticReferenceContext(type);
                        }
                    }

                    if (objectContext == nullptr)
                        objectContext = BindExpression(objectNode, scoped, scope, dataType);

                    std::vector<const DataType*> genericTypes;
                    for (const auto genericArgument: *funcRefNode->GetChild(0))
                        genericTypes.push_back(BindDataType(genericArgument, dataType->Parent()));

                    if (const auto function = objectContext->CreationType()->FindFunction(identifier->Value(), genericTypes); function != nullptr)
                    {
                        if (flag && !function->CheckDescriber(Describer::Static))
                        {
                            //exception
                        }

                        if (function->MemberType() == MemberType::VoidDefinition)
                        {
                            const auto action = Action::Instance(genericTypes);
                            return new FuncRef(objectContext, action);
                        }
                        if (function->MemberType() == MemberType::MethodDefinition)
                        {
                            genericTypes.push_back(function->CreationType());
                            const auto func = Func::Instance(genericTypes);

                            return new FuncRef(objectContext, func);
                        }
                    }

                    //exception
                    return new InvalidFuncRef(objectContext);
                }
            default:
                break;
        }

        //exception
        return new InvalidContext();
    }

    const ContextNode* BindBinaryExpression(const OverloadDefinition* const definition, const ContextNode* lhs, const ContextNode* rhs)
    {
        if (definition->MemberType() == MemberType::BuiltInOperation)
            return new BuiltInBinaryExpression(definition, lhs, rhs);

        return new DefinedBinaryExpression(definition, lhs, rhs);
    }

    const ContextNode* BindExpression(const ParseNode* expression, Scoped* const scoped, const Scope* const scope, const DataType* const dataType)
    {
        switch (expression->NodeType())
        {
            case NodeType::Unary:
                {
                    const auto unary = dynamic_cast<const UnaryNode*>(expression);
                    const auto kind = unary->Base().Kind();

                    const auto operand = BindExpression(unary->Operand(), scoped, scope, dataType);

                    if (kind.IsAssignment() && !operand->Writable())
                    {
                        //exception
                    }

                    auto args = std::vector<const DataType*>();
                    args.push_back(operand->CreationType());

                    const auto definition = operand->CreationType()->FindOverload(kind, args);
                    if (definition == nullptr)
                    {
                        //exception
                        return new InvalidUnaryExpression(operand);
                    }

                    if (definition->MemberType() == MemberType::BuiltInOperation)
                        return new BuiltInUnaryExpression(definition, operand);

                    return new DefinedUnaryExpression(definition, operand);
                }
            case NodeType::Binary:
                {
                    const auto binary = dynamic_cast<const BinaryNode*>(expression);
                    const auto kind = binary->Base().Kind();

                    const auto lhs = BindExpression(binary->LHS(), scoped, scope, dataType);
                    const auto rhs = BindExpression(binary->RHS(), scoped, scope, dataType);

                    if (kind.IsAssignment() && !lhs->Writable())
                    {
                        //exception
                    }

                    const auto lhsCreationType = lhs->CreationType();
                    const auto rhsCreationType = rhs->CreationType();

                    auto args = std::vector<const DataType*>();
                    if (lhsCreationType == rhsCreationType)
                    {
                        args.push_back(lhs->CreationType());
                        args.push_back(rhs->CreationType());

                        if (const auto definition = lhsCreationType->FindOverload(kind, args); definition != nullptr)
                            return BindBinaryExpression(definition, lhs, rhs);
                    }

                    const auto lhsCast = rhsCreationType->FindImplicitCast(rhsCreationType, lhsCreationType);
                    const auto rhsCast = lhsCreationType->FindImplicitCast(lhsCreationType, rhsCreationType);

                    args.push_back(lhsCreationType);
                    args.push_back(lhsCreationType);
                    const auto lhsOperation =  lhsCreationType->FindOverload(kind, args);
                    args.clear();

                    args.push_back(rhsCreationType);
                    args.push_back(rhsCreationType);
                    const auto rhsOperation =  rhsCreationType->FindOverload(kind, args);
                    args.clear();

                    const bool lhsValid = lhsCast != nullptr && rhsOperation != nullptr;
                    const bool rhsValid = rhsCast != nullptr && lhsOperation != nullptr;

                    if (lhsValid)
                    {
                        if (rhsValid)
                        {
                            //exception
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        return BindBinaryExpression(rhsOperation, lhs, BindCast(lhsCast, rhs));
                    }
                    if (rhsValid)
                        return BindBinaryExpression(rhsOperation, BindCast(rhsCast, lhs), rhs);

                    //exception
                    return new InvalidBinaryExpression(lhs, rhs);
                }
            case NodeType::Cast:
                {
                    const auto castNode = dynamic_cast<const CastExpressionNode*>(expression);

                    const auto operand = BindExpression(castNode->LHS(), scoped, scope, dataType);
                    const auto type = BindDataType(castNode->RHS(), dataType->Parent());

                    if (type == &Object::Instance())
                    {
                        if (operand->CreationType()->MemberType() == MemberType::Struct)
                            return new BoxCastExpression(operand);

                        return operand;
                    }
                    if (operand->CreationType() == &Object::Instance())
                    {
                        if (operand->CreationType()->MemberType() == MemberType::Class)
                            return new CastClassExpression(type, operand);

                        return new UnboxCastExpression(type, operand);
                    }

                    const auto operandCast = operand->CreationType()->FindExplicitCast(type, operand->CreationType());
                    const auto typeCast = type->FindExplicitCast(type, operand->CreationType());

                    return BindCast(operand, type, operandCast, typeCast);
                }
            default:
                return BindEntity(expression, scoped, scope, dataType);
        }
    }

    void BindStatement(const ParseNode* const statement, Scope* const scope, Scoped* const scoped, const DataType* const dataType)
    {
        switch (statement->NodeType())
        {
            case NodeType::Declaration:
                BindLocalDeclaration(dynamic_cast<const DeclarationNode*>(statement), scoped, scope, dataType);
                break;
            case NodeType::Initialisation:
                BindLocalDeclaration(dynamic_cast<const InitialisationNode*>(statement), scoped, scope, dataType);
                break;
            case NodeType::Expression:
                {
                    const auto expressionStatement = dynamic_cast<const ExpressionStatementNode*>(statement);
                    scope->AddChild(BindExpression(expressionStatement->Expression(), scoped, scope, dataType));
                }
                break;
            default:
                //exception
                break;
        }
    }

    void BindScope(const ScopeNode* const scopeNode, Scope* const scope, Scoped* const scoped, const DataType* const dataType)
    {
        auto current = scope;

        for (const auto child: *scopeNode)
        {
            switch (child->NodeType())
            {
                case NodeType::Expression:
                case NodeType::Declaration:
                case NodeType::Initialisation:
                    BindStatement(child, scope, scoped, dataType);
                    break;
                case NodeType::Break:
                    {
                        const auto name = current->FullName();
                        if (const auto pos = name.rfind(LOOP); pos != std::string::npos)
                        {
                            const auto result = std::format("{}_{}", name.substr(0, pos + LOOP.size()), END);
                            current->AddChild(new Branch(result));
                        }

                        //exception
                        current->AddChild(new InvalidContext());
                    }
                    break;
                case NodeType::Continue:
                    {
                        const auto name = current->FullName();
                        if (const auto pos = name.rfind(LOOP); pos != std::string::npos)
                        {
                            const auto result = std::format("{}_{}", name.substr(0, pos + LOOP.size()), POST);
                            current->AddChild(new Branch(result));
                        }

                        //exception
                        current->AddChild(new InvalidContext());
                    }
                    break;
                case NodeType::Return:
                    {
                        const auto returnNode = dynamic_cast<const ReturnNode*>(child);
                        if (const auto value = returnNode->Value(); value != nullptr)
                        {
                            const auto expression = BindExpression(value, scoped, current, dataType);
                            current->AddChild(new Return(expression->CreationType()));
                        }

                        current->AddChild(new Return());
                        return;
                    }
                case NodeType::IfChain:
                    {
                        const auto name = current->FullName();
                        const auto ifChainNode = dynamic_cast<const IfChainNode*>(child);

                        const auto ifScope = new Scope(ScopeType::Condition, std::format("{}_{}", name, CHECK), scoped);

                        for (int i = 0; i < ifChainNode->ChildCount(); i++)
                        {
                            const auto conditionNode = ifChainNode->GetChild(i);
                            const auto conditionScope = new Scope(ScopeType::ConditionScope, std::format("{}{}", ifScope->FullName(), i), scoped);

                            if (conditionNode->Condition() != nullptr)
                            {
                                const auto condition = BindExpression(conditionNode->Condition(), scoped, scope, dataType);
                                conditionScope->AddChild(condition);
                                if (i < ifChainNode->ChildCount() - 1)
                                    conditionScope->AddChild(new BranchFalse(std::format("{}{}", ifScope->FullName(), i + 1)));
                            }

                            BindScope(conditionNode->Body(), conditionScope, scoped, dataType);
                            ifScope->AddNested(conditionScope);
                        }

                        current->AddNested(ifScope);

                        const auto ifEnd = new Scope(ScopeType::Scope, std::format("{}_{}_{}", name, CHECK, END), scoped);
                        current->AddNested(ifEnd);
                        current = ifEnd;
                    }
                    break;
                case NodeType::For:
                    {
                        const auto name = current->FullName();
                        const auto forNode = dynamic_cast<const ForLoopNode*>(child);

                        const auto loopScope = new Scope(ScopeType::Loop, std::format("{}_{}", name, LOOP), scoped);
                        BindStatement(forNode->Pre(), loopScope, scoped, dataType);
                        current->AddNested(loopScope);

                        const auto conditionScope = new Scope(ScopeType::LoopCondition, std::format("{}_{}", loopScope->FullName(), CHECK), scoped);
                        conditionScope->AddChild(BindExpression(forNode->Condition(), scoped, current, dataType));
                        loopScope->AddNested(conditionScope);

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}", loopScope->FullName(), BODY), scoped);
                        BindScope(forNode->Body(), bodyScope, scoped, dataType);
                        loopScope->AddNested(bodyScope);

                        conditionScope->AddChild(new BranchTrue(bodyScope->FullName()));

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}", loopScope->FullName(), POST), scoped);
                        incrementBlock->AddChild(BindExpression(forNode->Post(), scoped, incrementBlock, dataType));
                        incrementBlock->AddChild(new Branch(conditionScope->FullName()));
                        loopScope->AddNested(incrementBlock);

                        const auto endBlock = new Scope(ScopeType::Scope, std::format("{}_{}", loopScope->FullName(), END), scoped);
                        current->AddNested(endBlock);

                        conditionScope->AddChild(new Branch(endBlock->FullName()));
                        current = endBlock;
                    }
                    break;
                case NodeType::While:
                    {
                        const auto name = current->FullName();
                        const auto whileNode = dynamic_cast<const WhileNode*>(child);

                        const auto conditionScope = new Scope(ScopeType::LoopCondition, std::format("{}_{}_{}", name, LOOP, CHECK), scoped);
                        conditionScope->AddChild(BindExpression(whileNode->Condition(), scoped, current, dataType));
                        current->AddNested(conditionScope);

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}_{}", name, LOOP, BODY), scoped);
                        BindScope(whileNode->Body(), bodyScope, scoped, dataType);
                        current->AddNested(bodyScope);

                        conditionScope->AddChild(new BranchTrue(bodyScope->FullName()));

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}_{}", name, LOOP, POST), scoped);
                        incrementBlock->AddChild(new Branch(conditionScope->FullName()));
                        current->AddNested(incrementBlock);

                        const auto endBlock = new Scope(ScopeType::Scope,std::format("{}_{}_{}", name, LOOP, END), scoped);
                        current->AddNested(endBlock);

                        conditionScope->AddChild(new Branch(endBlock->FullName()));
                        current = endBlock;
                    }
                    break;
                case NodeType::DoWhile:
                    {
                        const auto name = current->FullName();
                        const auto whileNode = dynamic_cast<const WhileNode*>(child);

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}_{}", name, LOOP, BODY), scoped);
                        BindScope(whileNode->Body(), bodyScope, scoped, dataType);
                        current->AddNested(bodyScope);

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}_{}", name, LOOP, POST), scoped);
                        incrementBlock->AddChild(BindExpression(whileNode->Condition(), scoped, current, dataType));
                        incrementBlock->AddChild(new BranchTrue(bodyScope->FullName()));
                        current->AddNested(incrementBlock);

                        const auto endBlock = new Scope(ScopeType::Scope, std::format("{}_{}_{}", name, LOOP, END), scoped);
                        current->AddNested(endBlock);
                        current = endBlock;
                    }
                    break;
                case NodeType::Scope:
                    {
                        const auto name = current->FullName();
                        const auto newScope = new Scope(ScopeType::Scope, std::format("{}_{}", name, SCOPE), scoped);
                        const auto newScopeNode = dynamic_cast<const ScopeNode*>(child);

                        BindScope(newScopeNode, newScope, scoped, dataType);
                        current->AddNested(newScope);

                        const auto continuation = new Scope(ScopeType::Scope, std::format("{}_{}", name, CONTINUATION), scoped);
                        current->AddNested(continuation);
                        current = continuation;
                    }
                    break;
                default:
                    {
                        //exception
                        current->AddChild(new InvalidContext());
                        break;
                    }
            }
        }
    }

    bool CheckCodePaths(const Scope* const scope, const DataType* const expected)
    {
        for (const auto context: *scope)
        {
            if (context->MemberType() == MemberType::Return)
            {
                if (context->CreationType() == expected)
                    return true;

                //exception
            }
        }

        bool result = false;
        for (int i = 0; i < scope->NestedCount(); i++)
        {
            if (const auto current = scope->NestedAt(i))
            {
                const auto type = current->Type();
                if (type == ScopeType::Scope)
                {
                    if (CheckCodePaths(current, expected))
                    {
                        result = true;
                        break;;
                    }
                }

                if (type == ScopeType::Condition)
                {
                    if (CheckCodePaths(current, expected))
                    {
                        if (const auto last = current->NestedAt(current->NestedCount() - 1); last->GetChild(0)->MemberType() != MemberType::BranchJump)
                        {
                            return true;
                            break;
                        }
                    }
                }

                if (type == ScopeType::ConditionScope)
                    result = CheckCodePaths(current, expected);
            }
        }

        return result;
    }

    void BindFunctions(DataType* const dataType)
    {
        for (const auto characteristic: dataType->AllCharacteristics())
        {
            if (characteristic.ParseNode() != nullptr)
                characteristic.WithDefault(BindExpression(characteristic.ParseNode()));
        }

        for (const auto function: dataType->AllFunctions())
        {
            BindScope(function->ParseNode(), function->Scope(), function, dataType);

            switch (function->MemberType())
            {
                case MemberType::Constructor:
                case MemberType::VoidDefinition:
                    break;
                case MemberType::ImplicitCast:
                case MemberType::ExplicitCast:
                case MemberType::OperatorOverload:
                case MemberType::MethodDefinition:
                    {
                        if (!CheckCodePaths(function->Scope(), function->CreationType()))
                        {
                            //exception
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void LocalBindSourceFile(const Structure::SourceFile* source)
    {
        for (const auto type: source->values())
        {
            BindFunctions(type);
        }
    }
}
