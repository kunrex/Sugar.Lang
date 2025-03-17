#include "global_binder.h"

#include <format>

#include "binder_extensions.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compilation/Analysis/static_binding_exception.h"
#include "../../../Exceptions/Compilation/Analysis/variable_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/return_accessibility_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/non_static_member_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/duplicate_function_definition_exception.h"

#include "../../../Lexing/Tokens/Factories/operator.h"

#include "../../../Parsing/ParseNodes/DataTypes/data_type_node.h"
#include "../../../Parsing/ParseNodes/Statements/declaration_node.h"
#include "../../../Parsing/ParseNodes/Properties/base_indexer_node.h"
#include "../../../Parsing/ParseNodes/Properties/base_property_node.h"
#include "../../../Parsing/ParseNodes/Statements/initialisation_node.h"
#include "../../../Parsing/ParseNodes/Expressions/Binary/binary_node.h"
#include "../../../Parsing/ParseNodes/Properties/assigned_property_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/explicit_cast_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/implicit_cast_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/function_creation_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/operator_overload_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/constructor_creation_node.h"

#include "../../Structure/DataTypes/enum.h"
#include "../../Structure/DataTypes/class.h"
#include "../../Structure/DataTypes/value_type.h"

#include "../../Structure/Global/BuiltIn/built_in_cast.h"

#include "../../Structure/Global/Properties/indexer.h"
#include "../../Structure/Global/Properties/property.h"

#include "../../Structure/Global/Variables/global_constant.h"
#include "../../Structure/Global/Variables/global_variable.h"

#include "../../Structure/Global/Functions/constructor.h"
#include "../../Structure/Global/Functions/explicit_cast.h"
#include "../../Structure/Global/Functions/implicit_cast.h"
#include "../../Structure/Global/Functions/void_function.h"
#include "../../Structure/Global/Functions/method_function.h"
#include "../../Structure/Global/Functions/operator_overload.h"

#include "../../Structure/Local/Variables/function_parameter.h"

#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Value/integer.h"

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Groups;
using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Properties;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;
using namespace ParseNodes::Functions::Creation;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string_view get_property_name = "get_Item";
constexpr std::string_view set_property_name = "set_Item";

constexpr std::string_view get_indexer_name = "get_Indexer";
constexpr std::string_view set_indexer_name = "set_Indexer";

namespace Analysis::Creation::Binding
{
    void ValidateStaticBinding(const Describable* const describable, const unsigned long index, const IUserDefinedType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static) && !describable->CheckDescriber(Describer::Static))
            PushException(new StaticBindingException(index, dataType->Parent()));
    }

    void MatchReturnAccessibility(const Characteristic* const characteristic, const unsigned long index, const IUserDefinedType* const dataType)
    {
        if (characteristic->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (characteristic->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void MatchReturnAccessibility(const Function* const function, const unsigned long index, const IUserDefinedType* const dataType)
    {
        if (function->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (function->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void BindEnumExpression(const ParseNode* const expression, Enum* const dataType)
    {
        switch (expression->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto identifier = *dynamic_cast<const IdentifierNode*>(expression);
                    const auto value = identifier.Value();
                    const auto index = identifier.Index();

                    if (dataType->FindCharacteristic(value) != nullptr)
                    {
                        PushException(new DuplicateVariableDefinitionException(index, dataType->Parent()));
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalConstant(value, Describer::Public | Describer::Constexpr, &Integer::Instance(), nullptr));
                }
                break;
            case NodeType::Binary:
                {
                    const auto casted = *dynamic_cast<const BinaryNode*>(expression);
                    const auto index = casted.Index();

                    if (casted.Base().Kind() != SyntaxKind::Assignment)
                    {
                        PushException(new InvalidGlobalStatementException(index, dataType->Parent()));
                        return;
                    }

                    const auto lhs = casted.LHS();
                    if (lhs->NodeType() != NodeType::Identifier)
                    {
                        PushException(new InvalidGlobalStatementException(index, dataType->Parent()));
                        return;
                    }

                    const auto identifier = *dynamic_cast<const IdentifierNode*>(lhs);
                    const auto value = identifier.Value();

                    if (dataType->FindCharacteristic(value) != nullptr)
                    {
                        PushException(new DuplicateVariableDefinitionException(index, dataType->Parent()));
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalConstant(value, Describer::Public | Describer::Constexpr, &Integer::Instance(), casted.RHS()));
                }
                break;
            default:
                PushException(new InvalidGlobalStatementException(expression->Index(), dataType->Parent()));
                break;
        }
    }

    void DeclareGlobalVariable(const DeclarationNode* const declarationNode, IUserDefinedType* const dataType)
    {
        const auto index = declarationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = declarationNode->Name()->Value();

        const auto creationType = BindDataType(declarationNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto describer = FromNode(declarationNode->Describer());
        const auto globalVariable = new GlobalVariable(identifier, describer == Describer::None ? Describer::Private : describer, creationType);

        MatchReturnAccessibility(globalVariable, index, dataType);

        ValidateStaticBinding(globalVariable, index, dataType);
        ValidateDescriber(globalVariable, Describer::AccessModifiers | Describer::Static, index, source);

        dataType->PushCharacteristic(globalVariable);
    }

    void InitialiseGlobalVariable(const InitialisationNode* const initialisationNode, IUserDefinedType* const dataType)
    {
        const auto index = initialisationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = initialisationNode->Name()->Value();

        const auto creationType = BindDataType(initialisationNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto describer = FromNode(initialisationNode->Describer());

        GlobalVariable* globalVariable;
        if ((describer & Describer::Constexpr) == Describer::Constexpr)
            globalVariable = new GlobalConstant(identifier, describer == Describer::None ? Describer::Private : describer, creationType, initialisationNode->Value());
        else
            globalVariable = new GlobalVariable(identifier, describer == Describer::None ? Describer::Private : describer, creationType, initialisationNode->Value());

        MatchReturnAccessibility(globalVariable, index, dataType);

        ValidateStaticBinding(globalVariable, index, dataType);
        ValidateDescriber(globalVariable, Describer::Constexpr | Describer::AccessModifiers | Describer::Static, index, source);

        dataType->PushCharacteristic(globalVariable);
    }

    std::tuple<MethodDefinition*, VoidDefinition*> CreatePropertyFunctions(const GetNode* const getNode, const SetNode* const setNode, const std::string& identifier, const Describer describer, const IDataType* const creationType)
    {
        MethodFunction* get; VoidFunction* set;

        if (getNode != nullptr)
        {
            const auto getName = std::format("{}_{}", get_property_name, identifier);
            const auto getDescriber = FromNode(getNode->Describer());

            auto actualDescriber = (getDescriber & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;
            if ((describer & Describer::Static) == Describer::Static)
                actualDescriber = actualDescriber | Describer::Static;

            get = new MethodFunction(getName, actualDescriber, creationType, getNode->Body());
        }

        if (setNode != nullptr)
        {
            const auto setName  = std::format("{}_{}", set_property_name, identifier);
            const auto setDescriber = FromNode(setNode->Describer());

            auto actualDescriber = (setDescriber & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            if ((describer & Describer::Static) == Describer::Static)
                actualDescriber = actualDescriber | Describer::Static;

            set = new VoidFunction(setName, actualDescriber, setNode->Body());
            set->AddParameter(new FunctionParameter("value", Describer::None, creationType));
        }

        return std::make_tuple(get, set);
    }

    void CreateProperty(const BasePropertyNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto index = propertyNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->Name()->Value();

        const auto creationType = BindDataType(propertyNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto provided = FromNode(propertyNode->Describer());
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result =  CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, actual, creationType);
        const auto property = new Property(identifier, actual, creationType, std::get<0>(result), std::get<1>(result));

        MatchReturnAccessibility(property, index, dataType);

        ValidateStaticBinding(property, index, dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, index, source);

        dataType->PushCharacteristic(property);
    }

    void InitialiseProperty(const AssignedPropertyNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto index = propertyNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->Name()->Value();

        const auto creationType = BindDataType(propertyNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(index, source));
            return;
        }

        const auto provided = FromNode(propertyNode->Describer());
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result =  CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, actual, creationType);
        const auto property = new Property(identifier, actual, creationType, std::get<0>(result), std::get<1>(result), propertyNode->Value());

        MatchReturnAccessibility(property, index, dataType);

        ValidateStaticBinding(property, index, dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, index, source);

        dataType->PushCharacteristic(property);
    }

    void BindFunctionParameters(const CompoundDeclarationNode* const declarationNode, std::vector<const IDataType*>& parameters, const SourceFile* const source)
    {
        for (const auto typeNode: *declarationNode)
            parameters.push_back(BindDataType(typeNode->Type(), source));
    }

    void BindFunctionParameters(IScoped* const scope, const std::vector<const IDataType*>& parameters, const CompoundDeclarationNode* const declarationNode, const SourceFile* const source)
    {
        for (int i = 0; i < declarationNode->ChildCount(); i++)
        {
            const auto current = *declarationNode->GetChild(i);

            const auto index = current.Index();
            const auto identifier = current.Name()->Value();
            const auto creationType = parameters.at(i);

            if (scope->GetParameterIndex(identifier))
            {
                PushException(new DuplicateVariableDefinitionException(index, source));
                continue;
            }

            const auto parameter = new FunctionParameter(identifier, FromNode(current.Describer()), creationType);
            ValidateDescriber(parameter, creationType->MemberType() == MemberType::Class ? Describer::None : Describer::Ref, index, source);

            scope->AddParameter(parameter);
        }
    }

    std::tuple<MethodDefinition*, VoidDefinition*> CreateIndexerFunctions(const GetNode* const getNode, const SetNode* const setNode, const CompoundDeclarationNode* declarationNode, const std::vector<const IDataType*>& parameters, const IDataType* const creationType, const Describer describer, const SourceFile* const source)
    {
        MethodFunction* get; VoidFunction* set;

        if (getNode != nullptr)
        {
            const auto actualDescriber = (FromNode(getNode->Describer()) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            get = new MethodFunction(std::string(get_indexer_name), actualDescriber, creationType, getNode->Body());
            BindFunctionParameters(get, parameters, declarationNode, source);
        }

        if (setNode != nullptr)
        {
            const auto actualDescriber = (FromNode(setNode->Describer()) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            set = new VoidFunction(std::string(set_indexer_name), actualDescriber, setNode->Body());
            BindFunctionParameters(set, parameters, declarationNode, source);

            if (set->GetParameterIndex("value"))
                PushException(new DuplicateVariableDefinitionException(declarationNode->Index(), source));
            else
                set->AddParameter(new FunctionParameter("value", Describer::None, creationType));
        }

        return std::make_tuple(get, set);
    }

    void CreateIndexer(const BaseIndexerNode* const indexerNode, IUserDefinedType* const dataType)
    {
        const auto index = indexerNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(indexerNode->Type(), source);
        const auto declarationNode = indexerNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindIndexer(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto provided = FromNode(indexerNode->Describer());
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result = CreateIndexerFunctions(indexerNode->Get(), indexerNode->Set(), declarationNode, parameters, creationType, actual, source);
        const auto indexer = new Indexer(actual, creationType, std::get<0>(result), std::get<1>(result));

        if (!creationType->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public) && indexer->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, source));

        ValidateDescriber(indexer, Describer::AccessModifiers, index, source);

        dataType->PushIndexer(indexer);
    }

    void CreateFunction(const FunctionCreationNode* const functionCreationNode, IUserDefinedType* const dataType)
    {
        const auto index = functionCreationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = functionCreationNode->Name()->Value();
        const auto declarationNode = functionCreationNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindFunction(identifier, parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto provided = FromNode(functionCreationNode->Describer());
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        FunctionDefinition* function;
        if (const auto typeNode = functionCreationNode->Type(); typeNode->NodeType() == NodeType::VoidType)
        {
            const auto voidDefinition = new VoidFunction(identifier, describer, functionCreationNode->Body());
            BindFunctionParameters(voidDefinition, parameters, declarationNode, source);

            function = voidDefinition;
        }
        else
        {
            const auto methodDefinition = new MethodFunction(identifier, describer, BindDataType(typeNode, source), functionCreationNode->Body());
            BindFunctionParameters(methodDefinition, parameters, declarationNode, source);

            function = methodDefinition;
        }

        MatchReturnAccessibility(function, index, dataType);

        ValidateStaticBinding(function, index, dataType);
        ValidateDescriber(function, Describer::Static | Describer::AccessModifiers, index, source);

        dataType->PushFunction(function);
    }

    void CreateConstructor(const ConstructorCreationNode* const constructorCreationNode, IUserDefinedType* const dataType)
    {
        const auto index = constructorCreationNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto declarationNode = constructorCreationNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindConstructor(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto provided = FromNode(constructorCreationNode->Describer());
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto constructor = new Constructor(describer, dataType, constructorCreationNode->Body());
        BindFunctionParameters(constructor, parameters, declarationNode, source);

        ValidateDescriber(constructor, Describer::AccessModifiers, index, source);

        dataType->PushConstructor(constructor);
    }

    void CreateExplict(const ExplicitCastNode* const explicitCastNode, IUserDefinedType* const dataType)
    {
        const auto index = explicitCastNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(explicitCastNode->Type(), source);
        const auto declarationNode = explicitCastNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (parameters.size() != 1)
        {
            PushException(new LogException("Explicit cast definition can contain only 1 parameter.", index, source));
            return;
        }

        const auto fromType = parameters[0];

        if (fromType != dataType && creationType != dataType)
        {
            PushException(new LogException("Return type or the argument of an explicit cast must the same as the type its defined in.", index, source));
            return;
        }

        if  (dataType->FindExplicitCast(creationType, fromType) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto explicitCast = new ExplicitCast(FromNode(explicitCastNode->Describer()), creationType, explicitCastNode->Body());
        BindFunctionParameters(explicitCast, parameters, declarationNode, source);

        MatchReturnAccessibility(explicitCast, index, dataType);

        if (!explicitCast->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, index, source));

        dataType->PushExplicitCast(explicitCast);
    }

    void CreateImplicit(const ImplicitCastNode* const implicitCastNode, IUserDefinedType* const dataType)
    {
        const auto index = implicitCastNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(implicitCastNode->Type(), source);
        const auto declarationNode = implicitCastNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (parameters.size() != 1)
        {
            PushException(new LogException("Implicit cast definition can contain only 1 parameter.", index, source));
            return;
        }

        const auto fromType = parameters[0];

        if (fromType != dataType && creationType != dataType)
        {
            PushException(new LogException("Return type or the argument of an implicit cast must the same as the type its defined in.", index, source));
            return;
        }

        if  (dataType->FindImplicitCast(creationType, fromType) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto implicitCast = new ImplicitCast(FromNode(implicitCastNode->Describer()), creationType, implicitCastNode->Body());
        BindFunctionParameters(implicitCast, parameters, declarationNode, source);

        MatchReturnAccessibility(implicitCast, index, dataType);

        if (!implicitCast->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, index, source));

        dataType->PushImplicitCast(implicitCast);
    }

    void CreateOperatorOverload(const OperatorOverloadNode* const operatorOverloadNode, IUserDefinedType* const dataType)
    {
        const auto index = operatorOverloadNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(operatorOverloadNode->Type(), source);
        if (creationType != dataType)
            PushException(new LogException(std::format("Expected return type: {}.", dataType->FullName()), index, source));

        const auto declarationNode = operatorOverloadNode->Parameters();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        const auto& token = operatorOverloadNode->Operator();

        if ((static_cast<OperatorKind>(token.Kind()) & OperatorKind::Assignment) == OperatorKind::Assignment)
            PushException(new LogException("Cannot overload the assignment operator or any of its derivatives", index, source));

        switch (token.Kind())
        {
            case SyntaxKind::Increment:
            case SyntaxKind::Decrement:
            case SyntaxKind::IncrementPrefix:
            case SyntaxKind::DecrementPrefix:
            case SyntaxKind::Not:
            case SyntaxKind::Plus:
            case SyntaxKind::Minus:
            case SyntaxKind::BitwiseNot:
            case SyntaxKind::BitwiseAnd:
                {
                    if (parameters.size() != 1)
                        PushException(new LogException(std::format("Expected 1 argument of type: {}.", dataType->FullName()), index, source));
                }
                break;
            default:
                {
                    if (parameters.size() != 2)
                        PushException(new LogException(std::format("Expected 2 arguments of type: {}.", dataType->FullName()), index, source));
                }
                break;
        }

        const auto operatorOverload = new OperatorOverload(token.Kind(), FromNode(operatorOverloadNode->Describer()), creationType, operatorOverloadNode->Body());
        BindFunctionParameters(operatorOverload, parameters, operatorOverloadNode->Parameters(), source);

        MatchReturnAccessibility(operatorOverload, index, dataType);

        if (!operatorOverload->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, index, source));

        dataType->PushOverload(operatorOverload);
    }

    void BindEnum(Enum* const enumSource)
    {
        for (const auto child: *enumSource->Skeleton()->Body())
        {
            switch (child->NodeType())
            {
                case NodeType::Expression:
                    BindEnumExpression(child, enumSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Index(), enumSource->Parent()));
                    break;
            }
        }

        enumSource->PushExplicitCast(new BuiltInCast(&String::Instance(), std::format("call instance string valuetype {}::ToString()", enumSource->FullName())));
    }

    void BindClass(ClassSource* const classSource)
    {
        for (const auto child: *classSource->Skeleton()->Body())
        {
            switch (child->NodeType())
            {
                case NodeType::Declaration:
                    DeclareGlobalVariable(dynamic_cast<const DeclarationNode*>(child), classSource);
                    break;
                case NodeType::Initialisation:
                    InitialiseGlobalVariable(dynamic_cast<const InitialisationNode*>(child), classSource);
                    break;
                case NodeType::Property:
                    CreateProperty(dynamic_cast<const BasePropertyNode*>(child), classSource);
                    break;
                case NodeType::PropertyInitialisation:
                    InitialiseProperty(dynamic_cast<const AssignedPropertyNode*>(child), classSource);
                    break;
                case NodeType::Indexer:
                    CreateIndexer(dynamic_cast<const BaseIndexerNode*>(child), classSource);
                    break;
                case NodeType::FunctionDeclaration:
                    CreateFunction(dynamic_cast<const FunctionCreationNode*>(child), classSource);
                    break;
                case NodeType::ConstructorDeclaration:
                    CreateConstructor(dynamic_cast<const ConstructorCreationNode*>(child), classSource);
                    break;
                case NodeType::ImplicitDeclaration:
                    CreateImplicit(dynamic_cast<const ImplicitCastNode*>(child), classSource);
                    break;
                case NodeType::ExplicitDeclaration:
                    CreateExplict(dynamic_cast<const ExplicitCastNode*>(child), classSource);
                    break;
                case NodeType::OperatorOverload:
                    CreateOperatorOverload(dynamic_cast<const OperatorOverloadNode*>(child), classSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Index(), classSource->Parent()));
                    break;
            }
        }

        if (classSource->CheckDescriber(Describer::Static))
            return;

        if (const auto explicitString = classSource->FindExplicitCast(&String::Instance(), classSource); explicitString == nullptr)
            classSource->PushExplicitCast(new BuiltInCast(&String::Instance(), std::format("call instance string class {}::ToString()", classSource->FullName())));

        if (const auto defaultConstructor = classSource->FindConstructor({ }); defaultConstructor == nullptr)
            classSource->PushConstructor(new DefaultConstructor(classSource));
    }

    void BindStruct(StructSource* const structSource)
    {
        for (const auto child: *structSource->Skeleton()->Body())
        {
            switch (child->NodeType())
            {
                case NodeType::Declaration:
                    DeclareGlobalVariable(dynamic_cast<const DeclarationNode*>(child), structSource);
                    break;
                case NodeType::Initialisation:
                    InitialiseGlobalVariable(dynamic_cast<const InitialisationNode*>(child), structSource);
                    break;
                case NodeType::Property:
                    CreateProperty(dynamic_cast<const BasePropertyNode*>(child), structSource);
                    break;
                case NodeType::PropertyInitialisation:
                    InitialiseProperty(dynamic_cast<const AssignedPropertyNode*>(child), structSource);
                    break;
                case NodeType::Indexer:
                    CreateIndexer(dynamic_cast<const BaseIndexerNode*>(child), structSource);
                    break;
                case NodeType::FunctionDeclaration:
                    CreateFunction(dynamic_cast<const FunctionCreationNode*>(child), structSource);
                    break;
                case NodeType::ConstructorDeclaration:
                    CreateConstructor(dynamic_cast<const ConstructorCreationNode*>(child), structSource);
                    break;
                case NodeType::ImplicitDeclaration:
                    CreateImplicit(dynamic_cast<const ImplicitCastNode*>(child), structSource);
                    break;
                case NodeType::ExplicitDeclaration:
                    CreateExplict(dynamic_cast<const ExplicitCastNode*>(child), structSource);
                    break;
                case NodeType::OperatorOverload:
                    CreateOperatorOverload(dynamic_cast<const OperatorOverloadNode*>(child), structSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Index(), structSource->Parent()));
                    break;
            }
        }

        if (structSource->CheckDescriber(Describer::Static))
            return;

        if (const auto explicitString = structSource->FindExplicitCast(&String::Instance(), structSource); explicitString == nullptr)
            structSource->PushExplicitCast(new BuiltInCast(&String::Instance(), std::format("callvirt instance string class {}::ToString()", structSource->FullName())));

        if (const auto defaultConstructor = structSource->FindConstructor({ }); defaultConstructor == nullptr)
            structSource->PushConstructor(new DefaultConstructor(structSource));
    }

    void GlobalBindSourceFile(const SourceFile* const source)
    {
        for (const auto type: source->values())
        {
            switch (type->MemberType())
            {
                case MemberType::Enum:
                    BindEnum(dynamic_cast<Enum*>(type));
                    break;
                case MemberType::Class:
                    BindClass(dynamic_cast<ClassSource*>(type));
                    break;
                case MemberType::ValueType:
                    BindStruct(dynamic_cast<StructSource*>(type));
                    break;
                default:
                    break;
            }
        }
    }
}
