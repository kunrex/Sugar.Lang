#include "local_binder.h"

#include <format>

#include "binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Local/read_write_exception.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compilation/Analysis/variable_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/accessibility_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/invalid_statement_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/overload_not_found_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/non_static_reference_exception.h"

#include "../../../Lexing/Tokens/Factories/operator.h"

#include "../../../Parsing/ParseNodes/Loops/while_node.h"
#include "../../../Parsing/ParseNodes/Groups/scope_node.h"
#include "../../../Parsing/ParseNodes/Loops/for_loop_node.h"
#include "../../../Parsing/ParseNodes/Groups/if_chain_node.h"
#include "../../../Parsing/ParseNodes/Constants/constant_node.h"
#include "../../../Parsing/ParseNodes/Conditions/condition_node.h"
#include "../../../Parsing/ParseNodes/Statements/declaration_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Unary/unary_node.h"
#include "../../../Parsing/ParseNodes/Statements/initialisation_node.h"
#include "../../../Parsing/ParseNodes/Statements/Control/return_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Binary/binary_node.h"
#include "../../../Parsing/ParseNodes/Expressions/dot_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/cast_expression_node.h"
#include "../../../Parsing/ParseNodes/Expressions/indexer_expression_node.h"
#include "../../../Parsing/ParseNodes/Statements/expression_statement_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/function_call_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/constructor_call_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/print_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/format_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/invoke_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/funcref_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/ref_call_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/BaseFunctions/copy_coll_node.h"
#include "../../../Parsing/ParseNodes/Functions/Calling/collection_construction_call_node.h"
#include "../../../Parsing/ParseNodes/Statements/throw_statement_node.h"

#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"

#include "../../Structure/Context/Control/branch.h"
#include "../../Structure/Context/Control/return.h"
#include "../../Structure/Context/invalid_context.h"
#include "../../Structure/Context/Entities/this_context.h"
#include "../../Structure/Context/Constants/null_constant.h"
#include "../../Structure/Context/Control/branch_condition.h"
#include "../../Structure/Context/Constants/float_constant.h"
#include "../../Structure/Context/Constants/string_constant.h"
#include "../../Structure/Context/Casts/box_cast_expression.h"
#include "../../Structure/Context/Constants/integer_constant.h"
#include "../../Structure/Context/Expressions/dot_expression.h"
#include "../../Structure/Context/Casts/cast_class_expression.h"
#include "../../Structure/Context/Casts/unbox_cast_expression.h"
#include "../../Structure/Context/Casts/defined_cast_expression.h"
#include "../../Structure/Context/Casts/invalid_cast_expression.h"
#include "../../Structure/Context/Expressions/indexer_expression.h"
#include "../../Structure/Context/Entities/Functions/ref_context.h"
#include "../../Structure/Context/Casts/built_in_cast_expression.h"
#include "../../Structure/Context/Entities/Functions/copy_context.h"
#include "../../Structure/Context/Entities/Functions/print_context.h"
#include "../../Structure/Context/Entities/Functions/input_context.h"
#include "../../Structure/Context/Entities/Functions/invoke_context.h"
#include "../../Structure/Context/Entities/static_reference_context.h"
#include "../../Structure/Context/Entities/throw_context.h"
#include "../../Structure/Context/Entities/Functions/format_context.h"
#include "../../Structure/Context/Entities/References/field_context.h"
#include "../../Structure/Context/Expressions/assignment_expression.h"
#include "../../Structure/Context/Entities/Functions/funcref_context.h"
#include "../../Structure/Context/Entities/Functions/creation_context.h"
#include "../../Structure/Context/Expressions/invalid_unary_expression.h"
#include "../../Structure/Context/Expressions/defined_unary_expression.h"
#include "../../Structure/Context/Entities/References/property_context.h"
#include "../../Structure/Context/Expressions/defined_binary_expression.h"
#include "../../Structure/Context/Expressions/built_in_unary_expression.h"
#include "../../Structure/Context/Entities/References/parameter_context.h"
#include "../../Structure/Context/Expressions/invalid_binary_expression.h"
#include "../../Structure/Context/Expressions/built_in_binary_expression.h"
#include "../../Structure/Context/Expressions/invalid_indexer_expression.h"
#include "../../Structure/Context/Entities/Functions/function_call_context.h"
#include "../../Structure/Context/Entities/References/local_variable_context.h"
#include "../../Structure/Context/Entities/Functions/invalid_funcref_context.h"
#include "../../Structure/Context/Entities/Functions/invalid_function_context.h"

#include "../../Structure/Global/Properties/property.h"

#include "../../Structure/Local/Scopes/scope.h"
#include "../../Structure/Local/Variables/local_variable.h"

#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/short.h"
#include "../../Structure/Wrappers/Generic/func.h"
#include "../../Structure/Wrappers/Generic/list.h"
#include "../../Structure/Wrappers/Value/double.h"
#include "../../Structure/Wrappers/Value/integer.h"
#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Generic/action.h"
#include "../../Structure/Wrappers/Value/character.h"
#include "../../Structure/Wrappers/Reference/object.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Generic/referenced.h"
#include "../../Structure/Wrappers/Reference/void.h"

using namespace Services;

using namespace Exceptions;

using namespace Tokens;
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

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string_view CHECK = "C";

constexpr std::string_view LOOP = "L";

constexpr std::string_view BODY = "B";
constexpr std::string_view POST = "P";
constexpr std::string_view END = "E";

constexpr std::string_view SCOPE = "S";
constexpr std::string_view CONTINUATION = "T";

namespace Analysis::Creation::Binding
{
    const ContextNode* BindEntity(const ParseNode* entity, IScoped* scoped, const Scope* scope, const IUserDefinedType* dataType);
    const ContextNode* BindEntity(const ParseNode* entity, const ContextNode* context, IScoped* scoped, const Scope* scope, const IUserDefinedType* dataType);

    const ContextNode* BindExpression(const ParseNode* expression, IScoped* scoped, const Scope* scope, const IUserDefinedType* dataType);

    bool VariableExists(const IdentifierNode* identifier, const IScoped* const scoped, const Scope* scope)
    {
        const auto value = identifier->Value();

        if (const auto local = scope->GetVariable(value); local > 0)
            return true;

        if (scoped->GetParameterIndex(value))
            return true;

        return false;
    }

    void BindLocalDeclaration(const DeclarationNode* declaration, const IScoped* const scoped, Scope* const scope, const IUserDefinedType* dataType)
    {
        const auto source = dataType->Parent();
        const auto index = declaration->Index();

        if (const auto identifierNode = declaration->Name(); VariableExists(identifierNode, scoped, scope))
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto describer = FromNode(declaration->Describer());
        const auto identifier = declaration->Name()->Value();

        switch (const auto typeNode = declaration->Type(); typeNode->NodeType())
        {
            case NodeType::VoidType:
            case NodeType::AnonymousType:
                PushException(new DuplicateVariableDefinitionException(index, source));
                break;
            default:
                {
                    const auto type = BindDataType(typeNode, dataType->Parent());
                    const auto variable = new LocalVariable(identifier, describer, type);

                    ValidateDescriber(variable, Describer::None, index, source);
                    scope->AddVariable(variable);
                }
                break;
        }
    }

    const ContextNode* BindCast(const IFunction* const definition, const ContextNode* const operand)
    {
        if (definition->MemberType() == MemberType::BuiltInCast)
            return new BuiltInCastExpression(definition, operand);

        return new DefinedCastExpression(definition, operand);
    }

    const ContextNode* BindCast(const ContextNode* const operand, const IDataType* const type, const IFunction* const operandCast, const IFunction* const typeCast, const unsigned long index, const SourceFile* const source)
    {
        const auto operandValid = operandCast != nullptr;
        const auto typeValid = typeCast != nullptr;

        if (operandValid)
        {
            if (typeValid)
            {
                 PushException(new LogException(std::format("Ambiguous cast between casts defined in: `{}` and `{}`", type->FullName(), operand->CreationType()->FullName()), index, source));
                 return new InvalidCastExpression(type, operand);
            }

            return BindCast(operandCast, operand);
        }
        if (typeValid)
            return BindCast(typeCast, operand);

        PushException(new LogException(std::format("No appropriate cast found from: `{}` to `{}`", type->FullName(), operand->CreationType()->FullName()), index, source));
        return new InvalidCastExpression(type, operand);
    }

    void BindLocalInitialisation(const InitialisationNode* const initialisation, IScoped* const scoped, Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = initialisation->Index();

        const auto identifierNode = initialisation->Name();
        if (VariableExists(identifierNode, scoped, scope))
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto describer = FromNode(initialisation->Describer());
        const auto identifier = identifierNode->Value();

        switch (const auto typeNode = initialisation->Type(); typeNode->NodeType())
        {
            case NodeType::VoidType:
                PushException(new DuplicateVariableDefinitionException(initialisation->Index(), dataType->Parent()));
                break;
            case NodeType::AnonymousType:
                {
                    const auto context = BindExpression(initialisation->Value(), scoped, scope, dataType);
                    const auto variable = new LocalVariable(identifier, describer, context->CreationType());

                    scope->AddChild(context);

                    ValidateDescriber(variable, Describer::None, index, source);
                    scope->AddVariable(variable);
                }
                break;
            default:
                {
                    const auto creationType = BindDataType(typeNode, dataType->Parent());
                    const IDataType* type;
                    if ((describer & Describer::Ref) == Describer::Ref)
                    {
                        if (creationType->MemberType() == MemberType::Class)
                        {
                            PushException(new LogException("Only value types may be referenced", index, source));
                            type = creationType;
                        }
                        else
                            type = Referenced::Instance(creationType);
                    }
                    else
                        type = creationType;

                    const auto variable = new LocalVariable(identifier, describer, type);
                    const auto value = BindExpression(initialisation->Value(), scoped, scope, dataType);

                    if (const auto valueType = value->CreationType(); valueType != type)
                    {
                        if (type == &Object::Instance())
                        {
                            if (valueType->MemberType() == MemberType::ValueType)
                                scope->AddChild(new BoxCastExpression(value));
                            else
                                scope->AddChild(value);
                        }
                        else
                        {
                            const auto valueCast = valueType->FindImplicitCast(type, valueType);
                            const auto resultCast = type->FindImplicitCast(type, valueType);

                            scope->AddChild(BindCast(value, type, valueCast, resultCast, index, source));
                        }
                    }
                    else
                        scope->AddChild(value);

                    ValidateDescriber(variable, Describer::Ref, index, source);
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

    const ContextNode* BindIdentifier(const IdentifierNode* identifier, const IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto value = identifier->Value();

        if (const auto local = scope->GetVariable(value); local)
        {
            const auto variable = scoped->VariableAt(*local);
            return new LocalVariableContext(variable, *local - scoped->ParameterCount());
        }

        if (const auto argument = scoped->GetParameterIndex(value); argument)
        {
            const auto variable = scoped->VariableAt(*argument);
            return new ParameterContext(variable, *argument + !scoped->CheckDescriber(Describer::Static));
        }

        if (const auto characteristic = dataType->FindCharacteristic(value); characteristic != nullptr)
        {
            if (scoped->CheckDescriber(Describer::Static) && !characteristic->CheckDescriber(Describer::Static))
                PushException(new NonStaticReferenceException(characteristic->FullName(), identifier->Index(), dataType->Parent()));

            switch (characteristic->MemberType())
            {
                case MemberType::Field:
                    return new FieldContext(characteristic);
                case MemberType::Property:
                    return new PropertyContext(dynamic_cast<const PropertyDefinition*>(characteristic));
                default:
                    break;
            }
        }

        return nullptr;
    }

    void BindArgumentContexts(const NodeCollection<ParseNode>* const functionNode, std::vector<const ContextNode*>& arguments, std::vector<const IDataType*>& argumentTypes, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        for (int i = 0; i < functionNode->ChildCount(); i++)
        {
            const auto current = functionNode->GetChild(i);
            const auto currentContext = BindExpression(current, scoped, scope, dataType);

            arguments.push_back(currentContext);
            argumentTypes.push_back(currentContext->CreationType());
        }
    }

    const ContextNode* CreateFunctionContext(const IFunctionDefinition* function, const std::vector<const ContextNode*>& arguments)
    {
        const auto functionContext = new FunctionCallContext(function);
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        return functionContext;
    }

    const ContextNode* CreateInvalidFunctionContext(const std::vector<const ContextNode*>& arguments, const std::string& identifier, const unsigned long index, const SourceFile* const source)
    {
        const auto functionContext = new InvalidFunctionContext();
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        PushException(new LogException(std::format("No appropriate overload for: `{}` was found", identifier), index, source));
        return functionContext;
    }

    const ContextNode* BindFunctionCall(const FunctionCallNode* functionNode, IScoped* const scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = functionNode->Index();

        const auto identifier = functionNode->Identifier()->Value();

        std::vector<const ContextNode*> arguments;
        std::vector<const IDataType*> argumentTypes;
        BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

        if (const auto function = dataType->FindFunction(identifier, argumentTypes); function != nullptr)
        {
            if (scoped->CheckDescriber(Describer::Static) && !function->CheckDescriber(Describer::Static))
                PushException(new NonStaticReferenceException(function->FullName(), index, source));

            return CreateFunctionContext(function, arguments);
        }

        return CreateInvalidFunctionContext(arguments, identifier, index, source);
    }

    const ContextNode* BindIndexerExpression(const IndexerExpressionNode* const indexerNode, const ContextNode* operand, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = indexerNode->Index();

        std::vector<const ContextNode*> arguments;
        std::vector<const IDataType*> argumentTypes;
        BindArgumentContexts(indexerNode, arguments, argumentTypes, scoped, scope, dataType);

        const auto creationType = operand->CreationType();
        if (const auto indexer = creationType->FindIndexer(argumentTypes); indexer != nullptr)
        {
            if (dataType != creationType && !indexer->CheckDescriber(Describer::Public))
                PushException(new AccessibilityException(std::format("{}::indexer", creationType->FullName()), index, source));

            const auto indexerContext = new IndexerExpression(indexer, operand);
            for (const auto argument: arguments)
                indexerContext->AddChild(argument);

            return indexerContext;
        }

        PushException(new LogException("No appropriate overload for indexer was found", index, source));
        const auto invalidIndexer = new InvalidIndexerExpression(operand);
        for (const auto argument: arguments)
            invalidIndexer->AddChild(argument);

        return invalidIndexer;
    }

    const ContextNode* BindDotLHS(const ParseNode* lhs, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
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
                if (scoped->CheckDescriber(Describer::Static))
                    PushException(new LogException("Using `this` in static context", lhs->Index(), dataType->Parent()));

                return new ThisContext(dataType);
            case NodeType::Constant:
                return BindConstant(dynamic_cast<const ConstantNode*>(lhs));
            case NodeType::Indexer:
                {
                    const auto indexerNode = dynamic_cast<const IndexerExpressionNode*>(lhs);
                    const auto operand = BindEntity(indexerNode->Operand(), scoped, scope, dataType);

                    return BindIndexerExpression(indexerNode, operand, scoped, scope, dataType);
                }
            default:
                break;
        }

        PushException(new InvalidStatementException(lhs->Index(), dataType->Parent()));
        return new InvalidContext();
    }

    const ContextNode* BindStaticDotRHS(const ParseNode* rhs, const ContextNode* context, IScoped* scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = rhs->Index();

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
                            PushException(new NonStaticReferenceException(characteristic->FullName(), index, source));
                        if (dataType != context->CreationType() && !characteristic->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(characteristic->FullName(), index, source));

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
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto function = context->CreationType()->FindFunction(identifier, argumentTypes); function != nullptr)
                    {
                        if (!function->CheckDescriber(Describer::Static))
                            PushException(new NonStaticReferenceException(function->Signature(), index, source));
                        if (dataType != context->CreationType() && !function->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(function->Signature(), index, source));

                        return new DotExpression(context, CreateFunctionContext(function, arguments));
                    }

                    return new DotExpression(context, CreateInvalidFunctionContext(arguments, identifier, index, source));
                }
            default:
                break;
        }

        PushException(new InvalidStatementException(index, source));
        return new DotExpression(context, new InvalidContext());
    }

    const ContextNode* BindEntity(const ParseNode* entity, const ContextNode* const context, IScoped* const scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = entity->Index();

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

                    const auto creationType = context->CreationType();
                    if (const auto characteristic = creationType->FindCharacteristic(identifier->Value()); characteristic != nullptr)
                    {
                        if (dataType != creationType && !characteristic->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(characteristic->FullName(), index, source));

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
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(functionNode, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto function = context->CreationType()->FindFunction(identifier, argumentTypes); function != nullptr)
                    {
                        if (dataType != context->CreationType() && !function->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(function->Signature(), index, source));

                        return new DotExpression(context, CreateFunctionContext(function, arguments));
                    }

                    return new DotExpression(context, CreateInvalidFunctionContext(arguments, identifier, index, source));
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

        PushException(new InvalidStatementException(index, source));
        return new DotExpression(context, new InvalidContext());
    }

    const ContextNode* BindPrint(const ContextNode* const operand, const bool ln)
    {
        if (operand->CreationType() == &Short::Instance())
            return new PrintShortContext(operand, ln);
        if (operand->CreationType() == &Integer::Instance())
            return new PrintIntContext(operand, ln);
        if (operand->CreationType() == &Long::Instance())
            return new PrintLongContext(operand, ln);
        if (operand->CreationType() == &Float::Instance())
            return new PrintFloatContext(operand, ln);
        if (operand->CreationType() == &Double::Instance())
            return new PrintDoubleContext(operand, ln);
        if (operand->CreationType() == &Character::Instance())
            return new PrintCharContext(operand, ln);
        if (operand->CreationType() == &Boolean::Instance())
            return new PrintBoolContext(operand, ln);
        if (operand->CreationType() == &String::Instance())
            return new PrintStringContext(operand, ln);

        return new PrintObjectContext(operand, ln);
    }

    const ContextNode* BindInvoke(const IDataType* creationType, const IDelegateType* delegateType, const std::vector<const ContextNode*>& arguments)
    {
        const auto invoke = new InvokeContext(creationType, delegateType);
        for (int i = 1; i < arguments.size(); i++)
            invoke->AddChild(arguments.at(i));

        return invoke;
    }

    const ContextNode* BindEntity(const ParseNode* entity, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
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
                return new InputContext();
            case NodeType::Print:
                {
                    if (const auto printNode = dynamic_cast<const PrintNode*>(entity); printNode->ChildCount() > 0)
                    {
                        const auto arg = printNode->GetChild(0);
                        const auto context = BindExpression(arg, scoped, scope, dataType);
                        return BindPrint(context, false);
                    }

                    return new PrintContext(false);
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

                    return new PrintContext(true);
                }
                break;
            case NodeType::Format:
                {
                    const auto formatNode = dynamic_cast<const FormatNode*>(entity);

                    std::vector<const ContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(formatNode, arguments, argumentTypes, scoped, scope, dataType);

                    const auto format = new FormatContext();
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

                    const auto delegate = arguments.at(0);
                    if (const auto delegateType = delegate->CreationType(); delegateType->Type() == TypeKind::Action)
                    {
                        const auto action = dynamic_cast<const Action*>(delegateType);

                        bool invalid = false;
                        for (int i = 0; i < arguments.size(); i++)
                        {
                            if (i >= action->TypeCount() || arguments[i + 1]->CreationType() != action->TypeAt(i))
                                invalid = true;
                        }

                        if (!invalid)
                            return BindInvoke(&Void::Instance(), action, arguments);
                    }
                    else if (delegateType->Type() == TypeKind::Action)
                    {
                        const auto func = dynamic_cast<const Func*>(delegateType);

                        bool invalid = false;
                        for (int i = 0; i < arguments.size(); i++)
                        {
                            if (i >= func->TypeCount() || arguments[i + 1]->CreationType() != func->TypeAt(i))
                                invalid = true;
                        }

                        if (!invalid)
                            return BindInvoke(func->TypeAt(func->TypeCount() - 1), func, arguments);
                    }

                    PushException(new LogException("Arguments do not match delegate signature", invokeNode->Index(), dataType->Parent()));
                    return new InvokeContext(&Object::Instance(), nullptr);
                }
                break;
            case NodeType::FuncRef:
                {
                    const auto source = dataType->Parent();

                    const auto funcRefNode = dynamic_cast<const FuncRefNode*>(entity);
                    const auto objectNode = funcRefNode->GetChild(0);

                    const auto functionCallNode = funcRefNode->GetChild(1);
                    if (functionCallNode->NodeType() != NodeType::Identifier)
                    {
                        PushException(new LogException("Expected name of the function as second argument", functionCallNode->Index(), source));
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

                    if (!objectContext->Readable())
                        PushException(new ReadException(objectNode->Index(), source));

                    std::vector<const IDataType*> genericTypes;
                    for (const auto genericArgument: *funcRefNode->GetChild(0))
                        genericTypes.push_back(BindDataType(genericArgument, dataType->Parent()));

                    if (const auto function = objectContext->CreationType()->FindFunction(identifier->Value(), genericTypes); function != nullptr)
                    {
                        if (flag && !function->CheckDescriber(Describer::Static))
                            PushException(new LogException(std::format("Trying to reference non static function: `{}`", function->Name()), entity->Index(), source));

                        if (function->MemberType() == MemberType::VoidDefinition)
                        {
                            const auto action = Action::Instance(genericTypes);
                            return new FuncRefContext(action, objectContext, function);
                        }
                        if (function->MemberType() == MemberType::MethodDefinition)
                        {
                            genericTypes.push_back(function->CreationType());
                            const auto func = Func::Instance(genericTypes);

                            return new FuncRefContext(func, objectContext, function);
                        }
                    }

                    PushException(new LogException("Couldn't find suitable function to reference", entity->Index(), source));
                    return new InvalidFuncRefContext(objectContext);
                }
            case NodeType::Ref:
                {
                    const auto refNode = dynamic_cast<const RefCallNode*>(entity);
                    const auto context = BindEntity(refNode->GetChild(0), scoped, scope, dataType);

                    if (!context->Readable() || context->CreationType()->MemberType() == MemberType::Class)
                    {
                        PushException(new LogException("Can only reference readable value type variables", entity->Index(), dataType->Parent()));
                        return context;
                    }

                    return new RefContext(context);
                }
            case NodeType::Copy:
                {
                    const auto copeNode = dynamic_cast<const CopyCallNode*>(entity);
                    const auto context = BindEntity(copeNode->GetChild(0), scoped, scope, dataType);

                    if (context->CreationType()->Type() != TypeKind::Referenced)
                        PushException(new LogException("Can only copy referenced variables", entity->Index(), dataType->Parent()));

                    return new CopyContext(context, dynamic_cast<const Referenced*>(context));
                }
            case NodeType::ConstructorCall:
                {
                    const auto source = dataType->Parent();

                    const auto constructorCallNode = dynamic_cast<const ConstructorCallNode*>(entity);
                    const auto creationType = BindDataType(constructorCallNode->Type(), dataType->Parent());

                    std::vector<const ContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(constructorCallNode, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto constructor = creationType->FindConstructor(argumentTypes); constructor != nullptr)
                    {
                        const auto context = new CreationContext(constructor);
                        for (const auto argument: arguments)
                            context->AddChild(context);

                        return context;
                    }

                    return CreateInvalidFunctionContext(arguments, creationType->FullName(), entity->Index(), source);
                }
            case NodeType::CollectionConstructorCall:
                {
                    const auto source = dataType->Parent();

                    const auto constructorCallNode = dynamic_cast<const CollectionConstructorCallNode*>(entity);
                    const auto creationType = BindDataType(constructorCallNode->Type(), dataType->Parent());

                    const auto collectionType = dynamic_cast<const ICollectionType*>(creationType);
                    const auto genericType = collectionType->GenericType();

                    std::vector<const ContextNode*> objects;
                    for (const auto child: *constructorCallNode)
                    {
                        const auto object = BindExpression(child, scoped, scope, dataType);
                        if (object->CreationType() != genericType)
                            PushException(new LogException(std::format("Expected argument of type: {}", genericType->FullName()), child->Index(), source));

                        objects.push_back(object);
                    }

                    const auto context = new CollectionCreationContext(collectionType);
                    for (auto object : objects)
                        context->AddChild(object);
                }
            default:
                break;
        }

        PushException(new InvalidStatementException(entity->Index(), dataType->Parent()));
        return new InvalidContext();
    }

    const ContextNode* BindBinaryExpression(const IFunction* const definition, const ContextNode* lhs, const ContextNode* rhs)
    {
        if (definition->MemberType() == MemberType::BuiltInOperation)
            return new BuiltInBinaryExpression(definition, lhs, rhs);

        return new DefinedBinaryExpression(definition, lhs, rhs);
    }

    const ContextNode* BindUnaryExpression(const IFunction* const definition, const ContextNode* operand)
    {
        if (definition->MemberType() == MemberType::BuiltInOperation)
            return new BuiltInUnaryExpression(definition, operand);

        return new DefinedUnaryExpression(definition, operand);
    }

    const ContextNode* BindExpression(const ParseNode* expression, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = expression->Index();

        switch (expression->NodeType())
        {
            case NodeType::Unary:
                {
                    const auto unary = dynamic_cast<const UnaryNode*>(expression);
                    const auto kind = unary->Base().Kind();

                    const auto operand = BindExpression(unary->Operand(), scoped, scope, dataType);

                    if (const auto operation = Operator::IsAssignment(kind); operation)
                    {
                        if (!operand->Writable())
                        {
                            PushException(new WriteException(index, source));;
                            return new InvalidUnaryExpression(operand);
                        }

                        const auto definition = operand->CreationType()->FindOverload(*operation);
                        if (definition == nullptr)
                        {
                            PushException(new OverloadNotFoundException(*operation, index, source));
                            return new InvalidUnaryExpression(operand);
                        }

                        return new AssignmentExpression(operand, BindUnaryExpression(definition, operand));
                    }

                    const auto definition = operand->CreationType()->FindOverload(kind);
                    if (definition == nullptr)
                    {
                        PushException(new OverloadNotFoundException(kind, index, source));
                        return new InvalidUnaryExpression(operand);
                    }

                    return BindUnaryExpression(definition, operand);
                }
            case NodeType::Binary:
                {
                    const auto binary = dynamic_cast<const BinaryNode*>(expression);
                    const auto kind = binary->Base().Kind();

                    const auto lhs = BindExpression(binary->LHS(), scoped, scope, dataType);
                    const auto rhs = BindExpression(binary->RHS(), scoped, scope, dataType);

                    if (kind == SyntaxKind::Assignment && lhs->Writable())
                        return new AssignmentExpression(lhs, rhs);

                    if (const auto operation = Operator::IsAssignment(kind); operation)
                    {
                        if (!lhs->Writable())
                        {
                            PushException(new WriteException(index, source));;
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        const auto definition = lhs->CreationType()->FindOverload(*operation);
                        if (definition == nullptr)
                        {
                            PushException(new OverloadNotFoundException(*operation, index, source));
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        return new AssignmentExpression(lhs, BindBinaryExpression(definition, lhs, rhs));
                    }

                    const auto lhsCreationType = lhs->CreationType();
                    const auto rhsCreationType = rhs->CreationType();

                    if (lhsCreationType == rhsCreationType)
                    {
                        if (const auto definition = lhsCreationType->FindOverload(kind); definition != nullptr)
                            return BindBinaryExpression(definition, lhs, rhs);

                        PushException(new OverloadNotFoundException(kind, index, source));
                        return new InvalidBinaryExpression(lhs, rhs);
                    }

                    const auto lhsCast = rhsCreationType->FindImplicitCast(rhsCreationType, lhsCreationType);
                    const auto rhsCast = lhsCreationType->FindImplicitCast(lhsCreationType, rhsCreationType);

                    const auto lhsOperation =  lhsCreationType->FindOverload(kind);
                    const auto rhsOperation =  rhsCreationType->FindOverload(kind);

                    const bool lhsValid = lhsCast != nullptr && rhsOperation != nullptr;
                    const bool rhsValid = rhsCast != nullptr && lhsOperation != nullptr;

                    if (lhsValid)
                    {
                        if (rhsValid)
                        {
                            PushException(new LogException(std::format("Ambiguous operation between overloads defined in: `{}` and `{}`", lhs->CreationType()->FullName(), rhs->CreationType()->FullName()), index, source));
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        return BindBinaryExpression(rhsOperation, lhs, BindCast(lhsCast, rhs));
                    }
                    if (rhsValid)
                        return BindBinaryExpression(rhsOperation, BindCast(rhsCast, lhs), rhs);

                    PushException(new LogException(std::format("No overload found for types: `{}` and `{}`", lhs->CreationType()->FullName(), rhs->CreationType()->FullName()), index, source));
                    return new InvalidBinaryExpression(lhs, rhs);
                }
            case NodeType::Cast:
                {
                    const auto castNode = dynamic_cast<const CastExpressionNode*>(expression);

                    const auto operand = BindExpression(castNode->LHS(), scoped, scope, dataType);
                    const auto type = BindDataType(castNode->RHS(), dataType->Parent());

                    if (type == &Object::Instance())
                    {
                        if (operand->CreationType()->MemberType() == MemberType::ValueType)
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

                    return BindCast(operand, type, operandCast, typeCast, index, source);
                }
            default:
                return BindEntity(expression, scoped, scope, dataType);
        }
    }

    void BindStatement(const ParseNode* const statement, Scope* const scope, IScoped* const scoped, const IUserDefinedType* const dataType)
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
                PushException(new InvalidStatementException(statement->Index(), dataType->Parent()));
                break;
        }
    }

    void BindScope(const NodeCollection<ParseNode>* const scopeNode, Scope* const scope, IScoped* const scoped, const IUserDefinedType* const dataType)
    {
        auto current = scope;

        for (const auto child: *scopeNode)
        {
            switch (child->NodeType())
            {
                case NodeType::Expression:
                case NodeType::Declaration:
                case NodeType::Initialisation:
                    BindStatement(child, current, scoped, dataType);
                    break;
                case NodeType::Throw:
                    {
                        const auto throwNode = dynamic_cast<const ThrowStatementNode*>(child);
                        current->AddChild(BindExpression(throwNode->Exception(), scoped, scope, dataType));
                        current->AddChild(new ThrowContext());
                    }
                    break;
                case NodeType::Break:
                    {
                        const auto name = current->FullName();
                        if (const auto pos = name.rfind(LOOP); pos != std::string::npos)
                        {
                            const auto result = std::format("{}_{}", name.substr(0, pos + LOOP.size()), END);
                            current->AddChild(new Branch(result));
                        }

                        PushException(new LogException("No loop found to break out of", child->Index(), dataType->Parent()));
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

                        PushException(new LogException("No loop found to continue to next iteration", child->Index(), dataType->Parent()));
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
                        PushException(new InvalidStatementException(child->Index(), dataType->Parent()));
                        current->AddChild(new InvalidContext());
                        break;
                    }
            }
        }
    }

    bool CheckCodePaths(const Scope* const scope, const IDataType* const expected, const unsigned long index, const IUserDefinedType* const dataType)
    {
        for (const auto context: *scope)
        {
            if (context->MemberType() == MemberType::Return)
            {
                if (context->CreationType() == expected)
                    return true;

                PushException(new LogException("Returned value does not match expected value", index, dataType->Parent()));
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
                    if (CheckCodePaths(current, expected, index, dataType))
                    {
                        result = true;
                        break;;
                    }
                }

                if (type == ScopeType::Condition)
                {
                    if (CheckCodePaths(current, expected, index, dataType))
                    {
                        if (const auto last = current->NestedAt(current->NestedCount() - 1); last->GetChild(0)->MemberType() != MemberType::BranchJump)
                            return true;
                    }
                }

                if (type == ScopeType::ConditionScope)
                    result = CheckCodePaths(current, expected, index, dataType);
            }
        }

        return result;
    }

    void BindFunctions(const IUserDefinedType* const dataType)
    {
        for (const auto function: dataType->AllScoped())
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
                        if (const auto scope = function->Scope(); !CheckCodePaths(scope, function->CreationType(), function->ParseNode()->Index(), dataType))
                            PushException(new LogException("Not all code paths return a value", function->ParseNode()->Index(), dataType->Parent()));
                    }
                    break;
                default:
                    break;
            }
        }

        if (dataType->MemberType() == MemberType::Enum)
            return;

        const auto staticConstructor = dataType->StaticConstructor();
        const auto instanceConstructor = dataType->InstanceConstructor();

        const auto staticScope = staticConstructor->Scope(), instanceScope = staticConstructor->Scope();

        for (const auto characteristic: dataType->AllCharacteristics())
        {
            const auto parseNode = characteristic->ParseNode();
            if (parseNode == nullptr)
                continue;

            if (characteristic->CheckDescriber(Describer::Static))
                staticScope->AddChild(new AssignmentExpression(new FieldContext(characteristic), BindExpression(parseNode, staticConstructor, staticScope, dataType)));
            else
                instanceScope->AddChild(new AssignmentExpression(new FieldContext(characteristic), BindExpression(parseNode, instanceConstructor, instanceScope, dataType)));
        }
    }

    void LocalBindSourceFile(const SourceFile* source)
    {
        for (const auto type: source->values())
            BindFunctions(type);
    }
}
