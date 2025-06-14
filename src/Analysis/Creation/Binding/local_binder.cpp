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

#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"

#include "../../Structure/Context/Control/throw.h"
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
#include "../../Structure/Context/Entities/Functions/copy_context.h"
#include "../../Structure/Context/Entities/Functions/print_context.h"
#include "../../Structure/Context/Entities/Functions/input_context.h"
#include "../../Structure/Context/Entities/Functions/invoke_context.h"
#include "../../Structure/Context/Entities/static_reference_context.h"
#include "../../Structure/Context/Entities/Functions/format_context.h"
#include "../../Structure/Context/Entities/References/field_context.h"
#include "../../Structure/Context/Expressions/assignment_expression.h"
#include "../../Structure/Context/Entities/Functions/funcref_context.h"
#include "../../Structure/Context/Entities/Functions/creation_context.h"
#include "../../Structure/Context/Expressions/invalid_unary_expression.h"
#include "../../Structure/Context/Expressions/defined_unary_expression.h"
#include "../../Structure/Context/Entities/References/property_context.h"
#include "../../Structure/Context/Expressions/defined_binary_expression.h"
#include "../../Structure/Context/Entities/References/parameter_context.h"
#include "../../Structure/Context/Expressions/invalid_binary_expression.h"
#include "../../Structure/Context/Expressions/invalid_indexer_expression.h"
#include "../../Structure/Context/Entities/Functions/function_call_context.h"
#include "../../Structure/Context/Entities/References/local_variable_context.h"
#include "../../Structure/Context/Entities/Functions/invalid_funcref_context.h"
#include "../../Structure/Context/Entities/Functions/invalid_function_context.h"
#include "../../Structure/Context/Expressions/duplicate_expression.h"
#include "../../Structure/Context/Expressions/invalid_ternary_expression.h"
#include "../../Structure/Context/Expressions/ternary_expression.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_collection_type.h"
#include "../../Structure/Core/Scoped/default_scoped.h"

#include "../../Structure/Global/Properties/property.h"

#include "../../Structure/Local/Scopes/scope.h"
#include "../../Structure/Local/Variables/local_variable.h"

#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/short.h"
#include "../../Structure/Wrappers/Generic/func.h"
#include "../../Structure/Wrappers/Value/double.h"
#include "../../Structure/Wrappers/Value/integer.h"
#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Reference/void.h"
#include "../../Structure/Wrappers/Generic/action.h"
#include "../../Structure/Wrappers/Value/character.h"
#include "../../Structure/Wrappers/Reference/object.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Generic/referenced.h"

using namespace std;

using namespace Services;

using namespace Exceptions;

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Compilation;
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
    const IContextNode* BindEntity(const IParseNode* entity, IScoped* scoped, const Scope* scope, const IUserDefinedType* dataType);
    const IContextNode* BindEntity(const IParseNode* entity, const IContextNode* context, IScoped* scoped, const Scope* scope, const IUserDefinedType* dataType);

    bool VariableExists(const IParseNode* identifier, const IScoped* const scoped, const Scope* scope)
    {
        const auto value = *identifier->Token().Value<string>();

        if (const auto local = scope->GetVariable(value); local > 0)
            return true;

        if (scoped->GetParameterIndex(value))
            return true;

        return false;
    }

    void BindLocalDeclaration(const Describer describer, const IDataType* const creationType, const IParseNode* const identifier, const IScoped* const scoped, Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = identifier->Token().Index();

        if (VariableExists(identifier, scoped, scope))
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto variable = new LocalVariable(*identifier->Token().Value<string>(), describer, creationType);
        ValidateDescriber(variable, Describer::None, index, source);

        scope->AddVariable(variable);
    }

    const IContextNode* BindCast(const IContextNode* const operand, const IDataType* const type, const IFunction* const operandCast, const IFunction* const typeCast, const unsigned long index, const SourceFile* const source)
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

            return new DefinedCastExpression(operandCast, operand);
        }
        if (typeValid)
            return new DefinedCastExpression(operandCast, operand);

        PushException(new LogException(std::format("No appropriate cast found from: `{}` to `{}`", type->FullName(), operand->CreationType()->FullName()), index, source));
        return new InvalidCastExpression(type, operand);
    }

    const IContextNode* TryBindCast(const IContextNode* const expression, const IDataType* const type, const unsigned long index, const SourceFile* const source)
    {
        const IContextNode* finalExpression = expression;
        if (const auto expressionType = expression->CreationType(); expressionType != type)
        {
            if (type == Object::Instance() && expressionType->MemberType() == MemberType::ValueType)
                finalExpression = new BoxCastExpression(expression);
            else
            {
                const auto valueCast = expressionType->FindImplicitCast(type, expressionType);
                const auto resultCast = expressionType->FindImplicitCast(type, expressionType);

                finalExpression = BindCast(expression, type, valueCast, resultCast, index, source);
            }
        }

        return finalExpression;
    }

    void BindLocalInitialisation(const Describer describer, const IDataType* const creationType, const IParseNode* const identifier, const IParseNode* const value, IScoped* const scoped, Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = identifier->Token().Index();

        if (VariableExists(identifier, scoped, scope))
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto variable = new LocalVariable(*identifier->Token().Value<string>(), describer, creationType);
        const auto finalExpression = TryBindCast(BindExpression(value, scoped, scope, dataType), creationType, index, source);

        scope->AddChild(new AssignmentExpression(new LocalVariableContext(variable, scoped->VariableCount() - scoped->ParameterCount()), finalExpression));

        ValidateDescriber(variable, Describer::Const | Describer::Ref, index, source);
        scope->AddVariable(variable);
    }

    void BindLocalDeclaration(const IParseNode* declaration, const IScoped* const scoped, Scope* const scope, const IUserDefinedType* dataType)
    {
        const auto source = dataType->Parent();
        const auto index = declaration->Token().Index();

        const auto identifier = declaration->GetChild(static_cast<int>(ChildCode::Identifier));

        switch (const auto typeNode = declaration->GetChild(static_cast<int>(ChildCode::Type)); typeNode->NodeType())
        {
            case NodeType::VoidType:
            case NodeType::AnonymousType:
                PushException(new DuplicateVariableDefinitionException(index, source));
                break;
            default:
                BindLocalDeclaration(FromNode(declaration->GetChild(static_cast<int>(ChildCode::Describer))), BindDataType(typeNode, dataType->Parent()), identifier, scoped, scope, dataType);
                break;
        }
    }

    const IDataType* ResolveInitialisationType(const IParseNode* const typeNode, const Describer describer, const SourceFile* const source)
    {
        const auto creationType = BindDataType(typeNode, source);
        const IDataType* type;
        if ((describer & Describer::Ref) == Describer::Ref)
        {
            if (creationType->MemberType() == MemberType::Class)
            {
                PushException(new LogException("Only value types may be referenced", typeNode->Token().Index(), source));
                type = creationType;
            }
            else
                type = Referenced::Instance(creationType);
        }
        else
            type = creationType;

        return type;
    }

    void BindLocalInitialisation(const IParseNode* const initialisation, IScoped* const scoped, Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = initialisation->Token().Index();

        const auto identifier = initialisation->GetChild(static_cast<int>(ChildCode::Identifier));

        switch (const auto typeNode = initialisation->GetChild(static_cast<int>(ChildCode::Type)); typeNode->NodeType())
        {
            case NodeType::VoidType:
                    PushException(new DuplicateVariableDefinitionException(typeNode->Token().Index(), dataType->Parent()));
                    break;
            case NodeType::AnonymousType:
                {
                    const auto context = BindExpression(initialisation->GetChild(static_cast<int>(ChildCode::Expression)), scoped, scope, dataType);
                    const auto variable = new LocalVariable(*identifier->Token().Value<string>(), FromNode(initialisation->GetChild(static_cast<int>(ChildCode::Describer))), context->CreationType());

                    scope->AddChild(new AssignmentExpression(new LocalVariableContext(variable, scoped->VariableCount() - scoped->ParameterCount()), context));

                    ValidateDescriber(variable, Describer::Const, index, source);
                    scope->AddVariable(variable);
                }
                break;
            default:
                {
                    const auto describer = FromNode(initialisation->GetChild(static_cast<int>(ChildCode::Describer)));
                    BindLocalInitialisation(FromNode(initialisation->GetChild(static_cast<int>(ChildCode::Describer))), ResolveInitialisationType(typeNode, describer, source), identifier, initialisation->GetChild(static_cast<int>(ChildCode::Expression)), scoped, scope, dataType);
                }
                break;
        }
    }

    void BindMultipleLocalDeclaration(const IParseNode* const statement, IScoped* const scoped, Scope* const scope, const IUserDefinedType* dataType)
    {
        switch (const auto typeNode = statement->GetChild(1); typeNode->NodeType())
        {
            case NodeType::VoidType:
            case NodeType::AnonymousType:
                PushException(new DuplicateVariableDefinitionException(typeNode->Token().Index(), dataType->Parent()));
                break;
            default:
                {
                    const auto describer = FromNode(statement->GetChild(0));
                    const auto creationType = ResolveInitialisationType(typeNode, describer, dataType->Parent());

                    const auto forceInit = creationType->Type() == TypeKind::Referenced;

                    const auto count = statement->ChildCount();
                    for (auto i = 2; i < count; i += 2)
                    {
                        const auto identifier = statement->GetChild(i);

                        if (const auto value = statement->GetChild(i + 1); value->NodeType() == NodeType::Empty)
                        {
                            if (forceInit)
                                PushException(new LogException("References must be initialised", identifier->Token().Index(), dataType->Parent()));

                            BindLocalDeclaration(describer, creationType, identifier, scoped, scope, dataType);
                        }
                        else
                            BindLocalInitialisation(describer, creationType, identifier, value, scoped, scope, dataType);
                    }
                }
                break;
        }
    }

    const IContextNode* BindConstant(const IParseNode* const constant)
    {
        switch (const auto& token = constant->Token(); static_cast<TypeKind>(token.Metadata()))
        {
            case TypeKind::Short:
                return new ShortConstant(static_cast<short>(token.Value<long>().value()));
            case TypeKind::Int:
                return new IntegerConstant(static_cast<int>(token.Value<long>().value()));
            case TypeKind::Long:
                return new LongConstant(token.Value<long>().value());
            case TypeKind::Float:
                return new FloatConstant(static_cast<float>(token.Value<double>().value()));
            case TypeKind::Double:
                return new DoubleConstant(token.Value<double>().value());
            case TypeKind::Character:
                return new CharacterConstant(static_cast<char>(token.Value<long>().value()));
            case TypeKind::Boolean:
                {
                    if (static_cast<bool>(token.Value<long>().value()))
                        return new TrueConstant();

                    return new FalseConstant();
                }
            case TypeKind::String:
                return new StringConstant(token.Value<std::string>().value());
            case TypeKind::Object:
                return new NullConstant();
            default:
                return new InvalidContext();
        }
    }

    const IContextNode* BindIdentifier(const IParseNode* identifier, const IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto value = *identifier->Token().Value<string>();

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
                PushException(new NonStaticReferenceException(characteristic->FullName(), identifier->Token().Index(), dataType->Parent()));

            switch (characteristic->MemberType())
            {
                case MemberType::Field:
                    return new FieldContext(characteristic, scoped->MemberType() == MemberType::Constructor);
                case MemberType::Property:
                    return new PropertyContext(dynamic_cast<const PropertyDefinition*>(characteristic), false);
                default:
                    break;
            }
        }

        return nullptr;
    }

    void BindArgumentContexts(const IParseNode* const functionNode, const int offset, std::vector<const IContextNode*>& arguments, std::vector<const IDataType*>& argumentTypes, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        for (int i = offset; i < functionNode->ChildCount(); i++)
        {
            const auto current = functionNode->GetChild(i);
            const auto currentContext = BindExpression(current, scoped, scope, dataType);

            arguments.push_back(currentContext);
            argumentTypes.push_back(currentContext->CreationType());
        }
    }

    const IContextNode* CreateFunctionContext(const IFunctionDefinition* function, const std::vector<const IContextNode*>& arguments)
    {
        const auto functionContext = new FunctionCallContext(function);
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        return functionContext;
    }

    const IContextNode* CreateInvalidFunctionContext(const std::vector<const IContextNode*>& arguments, const std::string& identifier, const unsigned long index, const SourceFile* const source)
    {
        const auto functionContext = new InvalidFunctionContext();
        for (const auto argument: arguments)
            functionContext->AddChild(argument);

        PushException(new LogException(std::format("No appropriate overload for: `{}` was found", identifier), index, source));
        return functionContext;
    }

    const IContextNode* BindFunctionCall(const IParseNode* const functionNode, IScoped* const scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = functionNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();
        const auto value = *identifier.Value<string>();

        std::vector<const IContextNode*> arguments;
        std::vector<const IDataType*> argumentTypes;
        BindArgumentContexts(functionNode, 1, arguments, argumentTypes, scoped, scope, dataType);

        if (const auto function = dataType->FindFunction(value, argumentTypes); function != nullptr)
        {
            if (scoped->CheckDescriber(Describer::Static) && !function->CheckDescriber(Describer::Static))
                PushException(new NonStaticReferenceException(function->FullName(), identifier.Index(), source));

            return CreateFunctionContext(function, arguments);
        }

        return CreateInvalidFunctionContext(arguments, value, identifier.Index(), source);
    }

    const IContextNode* BindIndexerExpression(const IParseNode* const indexerNode, const IContextNode* const operand, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = indexerNode->Token().Index();

        std::vector<const IContextNode*> arguments;
        std::vector<const IDataType*> argumentTypes;
        BindArgumentContexts(indexerNode, 1, arguments, argumentTypes, scoped, scope, dataType);

        const auto creationType = operand->CreationType();
        if (const auto indexer = creationType->FindIndexer(argumentTypes); indexer != nullptr)
        {
            if (dataType != creationType && !indexer->CheckDescriber(Describer::Public))
                PushException(new AccessibilityException(std::format("{}::indexer", creationType->FullName()), index, source));

            const auto indexerContext = new IndexerExpression(indexer, operand, creationType != dataType);
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

    const IContextNode* BindDotLHS(const IParseNode* const lhs, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        switch (lhs->NodeType())
        {
            case NodeType::Identifier:
                {
                    if (const auto characteristic = BindIdentifier(lhs, scoped, scope, dataType); characteristic != nullptr)
                        return characteristic;

                    if (const auto type = dataType->Parent()->GetReference(*lhs->Token().Value<string>()); type != nullptr)
                        return new StaticReferenceContext(type);
                }
                break;
            case NodeType::FunctionCall:
                return BindFunctionCall(lhs, scoped, scope, dataType);
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
                    PushException(new LogException("Using `this` in static context", lhs->Token().Index(), dataType->Parent()));

                return new ThisContext(dataType);
            case NodeType::Constant:
                return BindConstant(lhs);
            case NodeType::Indexer:
                {
                    const auto operand = BindEntity(lhs->GetChild(0), scoped, scope, dataType);
                    return BindIndexerExpression(lhs, operand, scoped, scope, dataType);
                }
            default:
                break;
        }

        PushException(new InvalidStatementException(lhs->Token().Index(), dataType->Parent()));
        return new InvalidContext();
    }

    const IContextNode* BindStaticDotRHS(const IParseNode* rhs, const IContextNode* context, IScoped* scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = rhs->Token().Index();

        switch (rhs->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto lhsContext = BindStaticDotRHS(rhs->GetChild(static_cast<int>(ChildCode::LHS)), context, scoped, scope, dataType);
                    if (!lhsContext->Readable())
                    {
                        PushException(new ReadException(rhs->Token().Index(), dataType->Parent()));
                        return new DotExpression(lhsContext, new InvalidContext());
                    }

                    const auto rhsContext = BindEntity(rhs->GetChild(static_cast<int>(ChildCode::RHS)), lhsContext, scoped, scope, dataType);

                    return new DotExpression(context, new DotExpression(lhsContext, rhsContext));
                }
            case NodeType::Identifier:
                {
                    if (const auto characteristic = context->CreationType()->FindCharacteristic(*rhs->Token().Value<string>()); characteristic != nullptr)
                    {
                        if (!characteristic->CheckDescriber(Describer::Static))
                            PushException(new NonStaticReferenceException(characteristic->FullName(), index, source));
                        if (dataType != context->CreationType() && !characteristic->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(characteristic->FullName(), index, source));

                        switch (characteristic->MemberType())
                        {
                            case MemberType::Field:
                                return new DotExpression(context, new FieldContext(characteristic, scoped->MemberType() == MemberType::Constructor));
                            case MemberType::Property:
                                return new DotExpression(context, new PropertyContext(dynamic_cast<const Property*>(characteristic), context->CreationType() != dataType));
                            default:
                                break;
                        }
                    }
                }
                break;
            case NodeType::FunctionCall:
                {
                    const auto identifier = *rhs->GetChild(0)->Token().Value<string>();

                    std::vector<const IContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(rhs, 1, arguments, argumentTypes, scoped, scope, dataType);

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

    const IContextNode* BindEntity(const IParseNode* const entity, const IContextNode* const context, IScoped* const scoped, const Scope* scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = entity->Token().Index();

        switch (entity->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto lhsContext = BindEntity(entity->GetChild(static_cast<int>(ChildCode::LHS)), context, scoped, scope, dataType);
                    if (!lhsContext->Readable())
                    {
                        PushException(new ReadException(entity->Token().Index(), dataType->Parent()));
                        return new DotExpression(lhsContext, new InvalidContext());
                    }

                    const auto rhsContext = BindEntity(entity->GetChild(static_cast<int>(ChildCode::RHS)), lhsContext, scoped, scope, dataType);

                    return new DotExpression(context, new DotExpression(lhsContext, rhsContext));
                }
            case NodeType::Identifier:
                {
                    const auto creationType = context->CreationType();
                    if (const auto characteristic = creationType->FindCharacteristic(*entity->Token().Value<string>()); characteristic != nullptr)
                    {
                        if (dataType != creationType && !characteristic->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(characteristic->FullName(), index, source));

                        const auto field = new FieldContext(characteristic, context->MemberType() == MemberType::ThisContext && scoped->MemberType() == MemberType::Constructor);
                        return new DotExpression(context, field);
                    }
                }
                break;
            case NodeType::FunctionCall:
                {
                    const auto identifier = *entity->GetChild(0)->Token().Value<string>();

                    std::vector<const IContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(entity, 1, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto function = context->CreationType()->FindFunction(identifier, argumentTypes); function != nullptr)
                    {
                        if (dataType != context->CreationType() && !function->CheckDescriber(Describer::Public))
                            PushException(new AccessibilityException(function->Signature(), index, source));

                        return new DotExpression(context, CreateFunctionContext(function, arguments));
                    }

                    return new DotExpression(context, CreateInvalidFunctionContext(arguments, identifier, index, source));
                }
            case NodeType::Indexer:
                return new DotExpression(context, BindIndexerExpression(entity, BindEntity(entity->GetChild(0), context, scoped, scope, dataType), scoped, scope, dataType));
            default:
                break;
        }

        PushException(new InvalidStatementException(index, source));
        return new DotExpression(context, new InvalidContext());
    }

    const IContextNode* BindFormat(const IParseNode* const formatNode, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        switch (formatNode->ChildCount())
        {
            case 2:
                {
                    const auto arg = BindExpression(formatNode->GetChild(0), scoped, scope, dataType);
                    const auto arg1 = BindExpression(formatNode->GetChild(1), scoped, scope, dataType);

                    if (arg->CreationType() != String::Instance())
                        PushException(new LogException("First argument of format must be a string", formatNode->Token().Index(), dataType->Parent()));

                    return new FormatSingleContext(arg, arg1->CreationType()->MemberType() == MemberType::Class ? arg1 : new BoxCastExpression(arg1));
                }
            case 3:
                {
                    const auto arg = BindExpression(formatNode->GetChild(0), scoped, scope, dataType);
                    const auto arg1 = BindExpression(formatNode->GetChild(1), scoped, scope, dataType);
                    const auto arg2 = BindExpression(formatNode->GetChild(2), scoped, scope, dataType);

                    if (arg->CreationType() != String::Instance())
                        PushException(new LogException("First argument of format must be a string", formatNode->Token().Index(), dataType->Parent()));

                    const auto actualArg1 = arg1->CreationType()->MemberType() == MemberType::Class ? arg1 : new BoxCastExpression(arg1);
                    const auto actualArg2 = arg2->CreationType()->MemberType() == MemberType::Class ? arg2 : new BoxCastExpression(arg2);

                    return new FormatDoubleContext(arg, actualArg1, actualArg2);
                }
                break;
            default:
                {
                    std::vector<const IContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(formatNode, 0, arguments, argumentTypes, scoped, scope, dataType);

                    if (argumentTypes[0] != String::Instance())
                        PushException(new LogException("First argument of format must be a string", formatNode->Token().Index(), dataType->Parent()));

                    const auto format = new FormatContext();
                    for (auto i = 0; i < argumentTypes.size(); i++)
                    {
                        if (const auto current = arguments[i]; argumentTypes[i]->MemberType() == MemberType::Class)
                            format->AddChild(current);
                        else
                            format->AddChild(new BoxCastExpression(current));
                    }

                    return format;
                }
        }
    }

    const IContextNode* BindPrint(const IContextNode* const operand, const bool ln)
    {
        if (operand->CreationType() == Short::Instance())
            return new PrintShortContext(operand, ln);
        if (operand->CreationType() == Integer::Instance())
            return new PrintIntContext(operand, ln);
        if (operand->CreationType() == Long::Instance())
            return new PrintLongContext(operand, ln);
        if (operand->CreationType() == Float::Instance())
            return new PrintFloatContext(operand, ln);
        if (operand->CreationType() == Double::Instance())
            return new PrintDoubleContext(operand, ln);
        if (operand->CreationType() == Character::Instance())
            return new PrintCharContext(operand, ln);
        if (operand->CreationType() == Boolean::Instance())
            return new PrintBoolContext(operand, ln);
        if (operand->CreationType() == String::Instance())
            return new PrintStringContext(operand, ln);

        return new PrintObjectContext(operand, ln);
    }

    const IContextNode* BindInvoke(const IDataType* creationType, const IDelegateType* delegateType, const std::vector<const IContextNode*>& arguments)
    {
        const auto invoke = new InvokeContext(creationType, delegateType);
        for (int i = 1; i < arguments.size(); i++)
            invoke->AddChild(arguments.at(i));

        return invoke;
    }

    const IContextNode* BindEntity(const IParseNode* entity, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        switch (entity->NodeType())
        {
            case NodeType::Dot:
                {
                    const auto lhs = BindDotLHS(entity->GetChild(static_cast<int>(ChildCode::LHS)), scoped, scope, dataType);

                    if (lhs->MemberType() == MemberType::StaticReferenceContext)
                        return BindStaticDotRHS(entity->GetChild(static_cast<int>(ChildCode::RHS)), lhs, scoped, scope, dataType);

                    if (!lhs->Readable())
                    {
                        PushException(new ReadException(entity->Token().Index(), dataType->Parent()));
                        return new DotExpression(lhs, new InvalidContext());
                    }

                    return BindEntity(entity->GetChild(static_cast<int>(ChildCode::RHS)), lhs, scoped, scope, dataType);
                }
            case NodeType::Constant:
                return BindConstant(entity);
            case NodeType::Identifier:
                {
                    if (const auto character = BindIdentifier(entity, scoped, scope, dataType); character != nullptr)
                        return character;
                }
                break;
            case NodeType::FunctionCall:
                return BindFunctionCall(entity, scoped, scope, dataType);
            case NodeType::Indexer:
                return BindIndexerExpression(entity, BindEntity(entity->GetChild(0), scoped, scope, dataType), scoped, scope, dataType);
            case NodeType::Input:
                return new InputContext();
            case NodeType::Format:
                return BindFormat(entity, scoped, scope, dataType);
            case NodeType::Invoke:
                {
                    std::vector<const IContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(entity, 0, arguments, argumentTypes, scoped, scope, dataType);

                    switch (const auto delegate = arguments.at(0); delegate->CreationType()->Type())
                    {
                        case TypeKind::Func:
                        case TypeKind::Action:
                            {
                                const auto delegateType = dynamic_cast<const IDelegateType*>(delegate->CreationType());
                                const auto typeCount = delegateType->TypeCount();

                                bool invalid = false;
                                for (int i = 1; i < arguments.size(); i++)
                                {
                                    if (i >= typeCount || argumentTypes[i] != delegateType->TypeAt(i - 1))
                                    {
                                        invalid = true;
                                        break;
                                    }
                                }

                                if (!invalid)
                                    return BindInvoke(delegate->CreationType()->Type() == TypeKind::Action ? Void::Instance() : delegateType->TypeAt(typeCount - 1), delegateType, arguments);
                            }
                            break;
                        default:
                            break;
                    }

                    PushException(new LogException("Arguments do not match delegate signature", entity->Token().Index(), dataType->Parent()));
                    return new InvokeContext(Object::Instance(), Action::Instance({ }));
                }
            case NodeType::FuncRef:
                {
                    const auto source = dataType->Parent();
                    const auto childCount = entity->ChildCount();

                    const auto objectNode = entity->GetChild(childCount - 2);

                    const auto functionCallNode = entity->GetChild(childCount - 1);
                    if (functionCallNode->NodeType() != NodeType::Identifier)
                    {
                        PushException(new LogException("Expected name of the function as second argument", functionCallNode->Token().Index(), source));
                        return new InvalidContext();
                    }

                    const auto identifier = *functionCallNode->Token().Value<string>();

                    bool flag = false;
                    const IContextNode* objectContext = nullptr;
                    if (objectNode->NodeType() == NodeType::Identifier)
                    {
                        if (const auto type = BindDataType(objectNode, dataType->Parent()); type != nullptr)
                        {
                            flag = true;
                            objectContext = new StaticReferenceContext(type);
                        }
                    }

                    if (objectContext == nullptr)
                        objectContext = BindExpression(objectNode, scoped, scope, dataType);

                    if (!objectContext->Readable())
                        PushException(new ReadException(objectNode->Token().Index(), source));

                    std::vector<const IDataType*> genericTypes(childCount - 2);
                    for (int i = 0; i < childCount - 2; i++)
                        genericTypes.push_back(BindDataType(entity->GetChild(i), dataType->Parent()));

                    if (const auto function = objectContext->CreationType()->FindFunction(identifier, genericTypes); function != nullptr)
                    {
                        if (flag && !function->CheckDescriber(Describer::Static))
                            PushException(new LogException(std::format("Trying to reference non static function: `{}`", function->Name()), entity->Token().Index(), source));

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

                    PushException(new LogException("Couldn't find suitable function to reference", entity->Token().Index(), source));
                    return new InvalidFuncRefContext(objectContext);
                }
            case NodeType::Ref:
                {
                    const auto context = BindEntity(entity->GetChild(0), scoped, scope, dataType);

                    if (!context->Readable() || context->CreationType()->MemberType() == MemberType::Class)
                    {
                        PushException(new LogException("Can only reference readable value type variables", entity->Token().Index(), dataType->Parent()));
                        return context;
                    }

                    return new RefContext(context);
                }
            case NodeType::Copy:
                {
                    const auto context = BindEntity(entity->GetChild(0), scoped, scope, dataType);

                    if (context->CreationType()->Type() != TypeKind::Referenced)
                        PushException(new LogException("Can only copy referenced variables", entity->Token().Index(), dataType->Parent()));

                    return new CopyContext(context, dynamic_cast<const Referenced*>(context));
                }
            case NodeType::ConstructorCall:
                {
                    const auto source = dataType->Parent();

                    const auto creationType = BindDataType(entity->GetChild(0), source);

                    std::vector<const IContextNode*> arguments;
                    std::vector<const IDataType*> argumentTypes;
                    BindArgumentContexts(entity, 1, arguments, argumentTypes, scoped, scope, dataType);

                    if (const auto constructor = creationType->FindConstructor(argumentTypes); constructor != nullptr)
                    {
                        const auto context = new CreationContext(constructor);
                        for (const auto argument: arguments)
                            context->AddChild(argument);

                        return context;
                    }

                    return CreateInvalidFunctionContext(arguments, creationType->FullName(), entity->Token().Index(), source);
                }
            case NodeType::CollectionConstructorCall:
                {
                    const auto source = dataType->Parent();

                    const auto creationType = BindDataType(entity->GetChild(0), source);

                    const auto collectionType = dynamic_cast<const ICollectionType*>(creationType);
                    const auto genericType = collectionType->GenericType();

                    std::vector<const IContextNode*> arguments;
                    for (int i = 1; i < entity->ChildCount(); i++)
                    {
                        const auto child = entity->GetChild(i);
                        const auto context = BindExpression(child, scoped, scope, dataType);
                        if (context->CreationType() != genericType)
                            PushException(new LogException(std::format("Expected argument of type: {}", genericType->FullName()), child->Token().Index(), source));

                        arguments.push_back(context);
                    }

                    const auto context = new CollectionCreationContext(collectionType);
                    for (const auto argument : arguments)
                        context->AddChild(argument);
                }
            default:
                break;
        }

        PushException(new InvalidStatementException(entity->Token().Index(), dataType->Parent()));
        return new InvalidContext();
    }

    const IContextNode* TryBindAssignmentCast(const IContextNode* const expression, const IDataType* const type, unsigned long index, const SourceFile* const sourceFile)
    {
        if (type->Type() == TypeKind::Referenced)
        {
            if (expression->CreationType() == type)
            {
                PushException(new LogException("Cannot reassign the value of a reference", index, sourceFile));
                return expression;
            }
            if (Referenced::Instance(expression->CreationType()) != type)
                PushException(new LogException("Cannot resolve type to reference", index, sourceFile));

            return expression;
        }

        return TryBindCast(expression, type, index, sourceFile);
    }

    const IContextNode* BindExpression(const IParseNode* expression, IScoped* const scoped, const Scope* const scope, const IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();
        const auto index = expression->Token().Index();

        switch (expression->NodeType())
        {
            case NodeType::Unary:
                {
                    const auto kind = expression->Token().Kind();

                    const auto operandNode = expression->GetChild(static_cast<int>(ChildCode::Expression));
                    const auto operand = BindExpression(operandNode, scoped, scope, dataType);

                    const IOperatorOverload* definition;
                    switch (kind)
                    {
                        case SyntaxKind::Increment:
                        case SyntaxKind::IncrementPrefix:
                            {
                                if (!operand->Writable())
                                {
                                    PushException(new WriteException(operandNode->Token().Index(), source));
                                    return new InvalidUnaryExpression(operand);
                                }

                                definition = operand->CreationType()->FindOverload(SyntaxKind::Increment);
                            }
                            break;
                        case SyntaxKind::Decrement:
                        case SyntaxKind::DecrementPrefix:
                            {
                                if (!operand->Writable())
                                {
                                    PushException(new WriteException(operandNode->Token().Index(), source));
                                    return new InvalidUnaryExpression(operand);
                                }

                                definition = operand->CreationType()->FindOverload(SyntaxKind::Decrement);
                            }
                            break;
                        default:
                            definition = operand->CreationType()->FindOverload(kind);
                            break;
                    }

                    if (definition == nullptr)
                    {
                        PushException(new OverloadNotFoundException(kind, index, source));
                        return new InvalidUnaryExpression(operand);
                    }

                    switch (kind)
                    {
                        case SyntaxKind::Increment:
                        case SyntaxKind::Decrement:
                            return new AssignmentExpression(operand, new DefinedUnaryExpression(definition, new DuplicateExpression(operand)));
                        case SyntaxKind::IncrementPrefix:
                        case SyntaxKind::DecrementPrefix:
                            return new AssignmentExpression(operand, new DuplicateExpression(new DefinedUnaryExpression(definition, operand)));
                        default:
                            return new DefinedUnaryExpression(definition, operand);
                    }
                }
            case NodeType::Binary:
                {
                    const auto kind = expression->Token().Kind();

                    const auto lhs = BindExpression(expression->GetChild(static_cast<int>(ChildCode::LHS)), scoped, scope, dataType);
                    const auto rhs = BindExpression(expression->GetChild(static_cast<int>(ChildCode::RHS)), scoped, scope, dataType);

                    if (kind == SyntaxKind::Assignment)
                    {
                        if (lhs->Writable())
                            return new AssignmentExpression(lhs, new DuplicateExpression(TryBindAssignmentCast(rhs, lhs->CreationType(), expression->Token().Index(), dataType->Parent())));

                        PushException(new WriteException(index, source));
                        return new InvalidBinaryExpression(lhs, rhs);
                    }
                    if (const auto operation = Operator::IsAssignment(kind); operation)
                    {
                        if (!lhs->Writable())
                        {
                            PushException(new WriteException(index, source));
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        const auto definition = lhs->CreationType()->FindOverload(*operation);
                        if (definition == nullptr)
                        {
                            PushException(new OverloadNotFoundException(*operation, index, source));
                            return new InvalidBinaryExpression(lhs, rhs);
                        }

                        return new AssignmentExpression(lhs, new DuplicateExpression(new DefinedBinaryExpression(definition, lhs, rhs)));
                    }

                    const auto lhsCreationType = lhs->CreationType();
                    const auto rhsCreationType = rhs->CreationType();

                    if (lhsCreationType == rhsCreationType)
                    {
                        if (const auto definition = lhsCreationType->FindOverload(kind); definition != nullptr)
                            return new DefinedBinaryExpression(definition, lhs, rhs);

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

                        return new DefinedBinaryExpression(rhsOperation, lhs, new DefinedCastExpression(lhsCast, rhs));
                    }
                    if (rhsValid)
                        return new DefinedBinaryExpression(rhsOperation, new DefinedCastExpression(rhsCast, lhs), rhs);

                    PushException(new LogException(std::format("No overload found for types: `{}` and `{}`", lhs->CreationType()->FullName(), rhs->CreationType()->FullName()), index, source));
                    return new InvalidBinaryExpression(lhs, rhs);
                }
            case NodeType::Cast:
                {
                    const auto operand = BindExpression(expression->GetChild(static_cast<int>(ChildCode::LHS)), scoped, scope, dataType);
                    const auto type = BindDataType(expression->GetChild(static_cast<int>(ChildCode::RHS)), dataType->Parent());

                    if (type == Object::Instance())
                    {
                        if (operand->CreationType()->MemberType() == MemberType::ValueType)
                            return new BoxCastExpression(operand);

                        return operand;
                    }
                    if (operand->CreationType() == Object::Instance())
                    {
                        if (operand->CreationType()->MemberType() == MemberType::Class)
                            return new CastClassExpression(type, operand);

                        return new UnboxCastExpression(type, operand);
                    }

                    const auto operandCast = operand->CreationType()->FindExplicitCast(type, operand->CreationType());
                    const auto typeCast = type->FindExplicitCast(type, operand->CreationType());

                    return BindCast(operand, type, operandCast, typeCast, index, source);
                }
            case NodeType::Ternary:
                {
                    const auto condition = BindExpression(expression->GetChild(static_cast<int>(ChildCode::Expression)), scoped, scope, dataType);

                    const auto trueValue = BindExpression(expression->GetChild(static_cast<int>(ChildCode::LHS)), scoped, scope, dataType);
                    const auto falseValue = BindExpression(expression->GetChild(static_cast<int>(ChildCode::RHS)), scoped, scope, dataType);

                    if (trueValue == falseValue)
                        return new TernaryExpression(trueValue->CreationType(), condition, trueValue, falseValue);

                    const auto trueType = trueValue->CreationType(), falseType = falseValue->CreationType();

                    const auto trueValid = trueType->FindImplicitCast(trueValue->CreationType(), falseValue->CreationType());
                    const auto falseValid = falseType->FindImplicitCast(falseValue->CreationType(), trueValue->CreationType());

                    if (trueValid != nullptr)
                    {
                        if (falseValid != nullptr)
                        {
                            PushException(new LogException("Cannot resolve return type of ternary expression. Try casting to a specific type to avoid redundancy", index, source));
                            return new InvalidTernaryExpression(condition, trueValue, falseValue);
                        }

                        return new TernaryExpression(trueType, condition, trueValue, new DefinedCastExpression(trueValid, falseValue));
                    }
                    if (falseValid != nullptr)
                        return new TernaryExpression(falseType, condition, new DefinedCastExpression(falseValid, trueValue), falseValue);

                    PushException(new LogException("Invalid Ternary Expression. True and False values must have same return type", index, source));
                    return new InvalidTernaryExpression(condition, trueValue, falseValue);
                }
            default:
                return BindEntity(expression, scoped, scope, dataType);
        }
    }

    void BindStatement(const IParseNode* const statement, Scope* const scope, IScoped* const scoped, const IUserDefinedType* const dataType)
    {
        switch (statement->NodeType())
        {
            case NodeType::Expression:
                scope->AddChild(BindExpression(statement->GetChild(static_cast<int>(ChildCode::Expression)), scoped, scope, dataType));
                break;
            case NodeType::Declaration:
                BindLocalDeclaration(statement, scoped, scope, dataType);
                break;
            case NodeType::Initialisation:
                BindLocalInitialisation(statement, scoped, scope, dataType);
                break;
            case NodeType::CompoundDeclaration:
                BindMultipleLocalDeclaration(statement, scoped, scope, dataType);
                break;
            default:
                PushException(new InvalidStatementException(statement->Token().Index(), dataType->Parent()));
                break;
        }
    }

    void BindScope(const IParseNode* const scopeNode, Scope* const scope, IScoped* const scoped, const IUserDefinedType* const dataType)
    {
        auto current = scope;
        const auto childCount = scopeNode->ChildCount();

        for (int i = 0; i < childCount; i++)
        {
            switch (const auto child = scopeNode->GetChild(i); child->NodeType())
            {
                case NodeType::Expression:
                case NodeType::Declaration:
                case NodeType::Initialisation:
                    BindStatement(child, current, scoped, dataType);
                    break;
                case NodeType::Print:
                    {
                        if (child->ChildCount() > 0)
                        {
                            const auto arg = child->GetChild(0);
                            const auto context = BindExpression(arg, scoped, scope, dataType);
                            current->AddChild(BindPrint(context, false));
                        }
                        else
                            current->AddChild(new PrintContext(false));
                    }
                    break;
                case NodeType::Println:
                    {
                        if (child->ChildCount() > 0)
                        {
                            const auto arg = child->GetChild(0);
                            const auto context = BindExpression(arg, scoped, scope, dataType);
                            current->AddChild(BindPrint(context, true));
                        }
                        else
                            current->AddChild(new PrintContext(true));
                    }
                    break;
                case NodeType::Throw:
                    {
                        current->AddChild(BindExpression(child->GetChild(static_cast<int>(ChildCode::Expression)), scoped, scope, dataType));
                        current->AddChild(new Throw());
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

                        PushException(new LogException("No loop found to break out of", child->Token().Index(), dataType->Parent()));
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

                        PushException(new LogException("No loop found to continue to next iteration", child->Token().Index(), dataType->Parent()));
                        current->AddChild(new InvalidContext());
                    }
                    break;
                case NodeType::Return:
                    {
                        if (const auto value = child->GetChild(static_cast<int>(ChildCode::Expression)); value != nullptr)
                        {
                            const auto expression = BindExpression(value, scoped, current, dataType);
                            current->AddChild(new Return(expression->CreationType()));

                            if (scoped->CreationType() != expression->CreationType())
                                PushException(new LogException(std::format("Return type does not match expected type: `{}`", scoped->CreationType()->FullName()), child->Token().Index(), dataType->Parent()));
                        }

                        current->AddChild(new Return());
                        if (scoped->CreationType() != Void::Instance())
                            PushException(new LogException("Unexpected return argument", child->Token().Index(), dataType->Parent()));
                    }
                    return;
                case NodeType::IfChain:
                    {
                        const auto name = current->FullName();
                        const auto ifCount = child->ChildCount();

                        const auto ifScope = new Scope(ScopeType::Condition, std::format("{}_{}", name, CHECK), scoped);
                        current->AddNested(ifScope);

                        for (auto k = 0; k < ifCount; k++)
                        {
                            const auto conditionNode = child->GetChild(k);

                            const auto conditionScope = new Scope(ScopeType::ConditionScope, std::format("{}{}", ifScope->FullName(), k), scoped);
                            ifScope->AddNested(conditionScope);

                            if (const auto condition = conditionNode->GetChild(static_cast<int>(ChildCode::Expression)); condition != nullptr)
                            {
                                conditionScope->AddChild(BindExpression(condition, scoped, current, dataType));
                                if (k < ifCount - 1)
                                    conditionScope->AddChild(new BranchFalse(std::format("{}{}", ifScope->FullName(), k + 1)));
                                else
                                    conditionScope->AddChild(new BranchFalse(std::format("{}_{}", ifScope->FullName(), END)));
                            }

                            BindScope(conditionNode->GetChild(static_cast<int>(ChildCode::Body)), conditionScope, scoped, dataType);
                        }

                        const auto ifEnd = new Scope(ScopeType::ConditionScope, std::format("{}_{}", ifScope->FullName(), END), scoped);
                        current->AddNested(ifEnd);
                        current = ifEnd;
                    }
                    break;
                case NodeType::For:
                    {
                        const auto name = current->FullName();

                        const auto loopScope = new Scope(ScopeType::Loop, std::format("{}_{}", name, LOOP), scoped);
                        current->AddNested(loopScope);

                        BindStatement(child->GetChild(static_cast<int>(ChildCode::Pre)), loopScope, scoped, dataType);

                        const auto conditionScope = new Scope(ScopeType::LoopCondition, std::format("{}_{}", loopScope->FullName(), CHECK), scoped);
                        loopScope->AddNested(conditionScope);

                        conditionScope->AddChild(BindExpression(child->GetChild(static_cast<int>(ChildCode::Expression)), scoped, loopScope, dataType));

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}", loopScope->FullName(), BODY), scoped);
                        loopScope->AddNested(bodyScope);

                        BindScope(child->GetChild(static_cast<int>(ChildCode::Body)), bodyScope, scoped, dataType);

                        conditionScope->AddChild(new BranchTrue(bodyScope->FullName()));

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}", loopScope->FullName(), POST), scoped);
                        loopScope->AddNested(incrementBlock);

                        incrementBlock->AddChild(BindExpression(child->GetChild(static_cast<int>(ChildCode::Post)), scoped, loopScope, dataType));
                        incrementBlock->AddChild(new Branch(conditionScope->FullName()));

                        const auto endBlock = new Scope(ScopeType::Scope, std::format("{}_{}", loopScope->FullName(), END), scoped);
                        current->AddNested(endBlock);

                        conditionScope->AddChild(new Branch(endBlock->FullName()));
                        current = endBlock;
                    }
                    break;
                case NodeType::While:
                    {
                        const auto name = current->FullName();

                        const auto conditionScope = new Scope(ScopeType::LoopCondition, std::format("{}_{}_{}", name, LOOP, CHECK), scoped);
                        current->AddNested(conditionScope);

                        conditionScope->AddChild(BindExpression(child->GetChild(static_cast<int>(ChildCode::Expression)), scoped, current, dataType));

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}_{}", name, LOOP, BODY), scoped);
                        current->AddNested(bodyScope);

                        BindScope(child->GetChild(static_cast<int>(ChildCode::Body)), bodyScope, scoped, dataType);

                        conditionScope->AddChild(new BranchTrue(bodyScope->FullName()));

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}_{}", name, LOOP, POST), scoped);
                        current->AddNested(incrementBlock);

                        incrementBlock->AddChild(new Branch(conditionScope->FullName()));

                        const auto endBlock = new Scope(ScopeType::Scope,std::format("{}_{}_{}", name, LOOP, END), scoped);
                        current->AddNested(endBlock);

                        conditionScope->AddChild(new Branch(endBlock->FullName()));
                        current = endBlock;
                    }
                    break;
                case NodeType::DoWhile:
                    {
                        const auto name = current->FullName();

                        const auto bodyScope = new Scope(ScopeType::LoopBody, std::format("{}_{}_{}", name, LOOP, BODY), scoped);
                        current->AddNested(bodyScope);

                        BindScope(child->GetChild(static_cast<int>(ChildCode::Body)), bodyScope, scoped, dataType);

                        const auto incrementBlock = new Scope(ScopeType::Increment, std::format("{}_{}_{}", name, LOOP, POST), scoped);
                        current->AddNested(incrementBlock);

                        incrementBlock->AddChild(BindExpression(child->GetChild(static_cast<int>(ChildCode::Expression)), scoped, current, dataType));
                        incrementBlock->AddChild(new BranchTrue(bodyScope->FullName()));

                        const auto endBlock = new Scope(ScopeType::Scope, std::format("{}_{}_{}", name, LOOP, END), scoped);
                        current->AddNested(endBlock);
                        current = endBlock;
                    }
                    break;
                case NodeType::Scope:
                    {
                        const auto name = current->FullName();
                        const auto newScope = new Scope(ScopeType::Scope, std::format("{}_{}", name, SCOPE), scoped);
                        current->AddNested(newScope);

                        BindScope(child, newScope, scoped, dataType);

                        const auto continuation = new Scope(ScopeType::Scope, std::format("{}_{}", name, CONTINUATION), scoped);
                        current->AddNested(continuation);
                        current = continuation;
                    }
                    break;
                default:
                    {
                        PushException(new InvalidStatementException(child->Token().Index(), dataType->Parent()));
                        current->AddChild(new InvalidContext());
                        break;
                    }
            }
        }
    }

    bool IsReturnComplete(const Scope* const scope, const IDataType* const expected)
    {
        for (const auto context: *scope)
        {
            if (context->MemberType() == MemberType::Return)
            {
                if (context->CreationType() == expected)
                    return true;

                return false;
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
                    if (IsReturnComplete(current, expected))
                    {
                        result = true;
                        break;
                    }
                }

                if (type == ScopeType::Condition)
                {
                    if (IsReturnComplete(current, expected))
                    {
                        if (const auto last = current->NestedAt(current->NestedCount() - 1); last->GetChild(0)->MemberType() != MemberType::BranchJump)
                            return true;
                    }
                }

                if (type == ScopeType::ConditionScope)
                    result = IsReturnComplete(current, expected);
            }
        }

        return result;
    }
}
