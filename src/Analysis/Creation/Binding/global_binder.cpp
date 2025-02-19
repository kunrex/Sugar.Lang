#include "global_binder.h"

#include <format>

#include "binder_extensions.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
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
#include "../../../Parsing/ParseNodes/Statements/expression_statement_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/explicit_cast_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/implicit_cast_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/function_creation_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/operator_overload_node.h"
#include "../../../Parsing/ParseNodes/Functions/Creation/constructor_creation_node.h"

#include "../../Structure/Nodes/DataTypes/enum.h"
#include "../../Structure/Nodes/DataTypes/class.h"

#include "../../Structure/Nodes/Global/Properties/indexer.h"
#include "../../Structure/Nodes/Global/Properties/property.h"

#include "../../Structure/Nodes/Global/Variables/global_variable.h"

#include "../../Structure/Nodes/Global/UserDefined/constructor.h"
#include "../../Structure/Nodes/Global/UserDefined/explicit_cast.h"
#include "../../Structure/Nodes/Global/UserDefined/implicit_cast.h"
#include "../../Structure/Nodes/Global/UserDefined/void_function.h"
#include "../../Structure/Nodes/Global/UserDefined/method_function.h"
#include "../../Structure/Nodes/Global/UserDefined/operator_overload.h"

#include "../../Structure/Nodes/Local/Variables/function_parameter.h"

#include "../../Structure/Wrappers/Value/integer.h"

using namespace Exceptions;

using namespace Tokens::Enums;

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
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::DataTypes;

constexpr std::string_view get_property_name = "get_item";
constexpr std::string_view set_property_name = "set_item";

constexpr std::string_view get_indexer_name = "get_indexer";
constexpr std::string_view set_indexer_name = "set_indexer";

namespace Analysis::Creation::Binding
{
    void MatchReturnAccessibility(const Characteristic* const characteristic, const unsigned long index, const DataType* const dataType)
    {
        if (characteristic->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (characteristic->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void MatchReturnAccessibility(const Function* const function, const unsigned long index, const DataType* const dataType)
    {
        if (function->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (function->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void MatchReturnAccessibility(const IndexerDefinition* const indexer, const unsigned long index, const DataType* const dataType)
    {
        if (indexer->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (indexer->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void BindEnumExpression(const ExpressionStatementNode* const expressionNode, DataType* const dataType)
    {
        switch (const auto expression = expressionNode->Expression(); expression->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto identifier = *dynamic_cast<const IdentifierNode*>(expression);
                    const auto value = identifier.Value();
                    const auto index = identifier.Index();

                    if (dataType->FindCharacteristic(value) != nullptr)
                        PushException(new DuplicateVariableDefinitionException(value, index, dataType->Parent()));
                    else
                        dataType->PushCharacteristic(new GlobalVariable(value, Describer::Public | Describer::Const, &Integer::Instance()));
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
                        PushException(new DuplicateVariableDefinitionException(value, index, dataType->Parent()));
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalVariable(value, Describer::Public | Describer::Const, &Integer::Instance(), casted.RHS()));
                }
                break;
            default:
                PushException(new InvalidGlobalStatementException(expression->Index(), dataType->Parent()));
                break;
        }
    }

    void DeclareGlobalVariable(const DeclarationNode* const declarationNode, DataType* const dataType)
    {
        const auto index = declarationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = declarationNode->Name()->Value();

        const auto creationType = BindDataType(declarationNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier, index, source));
            return;
        }

        const auto globalVariable = new GlobalVariable(identifier, FromNode(declarationNode->Describer()), creationType);

        MatchReturnAccessibility(globalVariable, index, dataType);
        ValidateDescriber(globalVariable, Describer::ValidMembers, index, source);

        dataType->PushCharacteristic(globalVariable);
    }

    void InitialiseGlobalVariable(const InitialisationNode* const initialisationNode, DataType* const dataType)
    {
        const auto index = initialisationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = initialisationNode->Name()->Value();

        const auto creationType = BindDataType(initialisationNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier, index, source));
            return;
        }

        const auto globalVariable = new GlobalVariable(identifier, FromNode(initialisationNode->Describer()), creationType, initialisationNode->Value());

        MatchReturnAccessibility(globalVariable, index, dataType);
        ValidateDescriber(globalVariable, Describer::ValidMembers, index, source);

        dataType->PushCharacteristic(globalVariable);
    }

    void CreatePropertyFunctions(const GetNode* const getNode, const SetNode* const setNode, const std::string& identifier, const Describer describer, const DataType* const creationType, const MethodFunction*& get, VoidFunction*& set)
    {
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
            set->AddArgument(new FunctionParameter("value", Describer::Const, creationType));
        }
    }

    void CreateProperty(const BasePropertyNode* const propertyNode, DataType* const dataType)
    {
        const auto index = propertyNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->Name()->Value();

        const auto creationType = BindDataType(propertyNode->Type(), source);

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier, index, source));
            return;
        }

        const auto describer = FromNode(propertyNode->Describer());

        const MethodFunction* get = nullptr;  VoidFunction* set = nullptr;
        CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, describer, creationType, get, set);

        const auto property = new Property(identifier, describer, creationType, get, set);

        MatchReturnAccessibility(property, index, dataType);
        ValidateDescriber(property, Describer::ValidMembers, index, source);

        dataType->PushCharacteristic(property);
    }

    void InitialiseProperty(const AssignedPropertyNode* const propertyNode, DataType* const dataType)
    {
        const auto index = propertyNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->Name()->Value();

        const auto creationType = BindDataType(propertyNode->Type(), source);

        const auto describer = FromNode(propertyNode->Describer());

        const MethodFunction* get = nullptr; VoidFunction* set = nullptr;
        CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, describer, creationType, get, set);

        const auto property = new Property(identifier, describer, creationType, get, set, propertyNode->Value());

        MatchReturnAccessibility(property, index, dataType);
        ValidateDescriber(property, Describer::ValidMembers, index, source);

        dataType->PushCharacteristic(property);
    }

    void BindFunctionParameters(const CompoundDeclarationNode* const declarationNode, std::vector<const DataType*>& parameters, const SourceFile* const source)
    {
        for (const auto typeNode: *declarationNode)
            parameters.push_back(BindDataType(typeNode->Type(), source));
    }

    void BindFunctionParameters(Scoped* const scope, const std::vector<const DataType*>& parameters, const CompoundDeclarationNode* const declarationNode, const SourceFile* const source)
    {
        for (int i = 0; i < declarationNode->ChildCount(); ++i)
        {
            const auto current = *declarationNode->GetChild(i);

            const auto index = current.Index();
            const auto identifier = current.Name()->Value();

            const auto creationType = parameters.at(i);

            if (scope->ContainsArgument(identifier))
            {
                PushException(new DuplicateVariableDefinitionException(identifier, index, source));
                continue;
            }

            const auto parameter = new FunctionParameter(identifier, FromNode(current.Describer()), creationType);

            const auto validDescribers = Describer::Const | (creationType->MemberType() == MemberType::Struct ? Describer::Ref : Describer::None);
            ValidateDescriber(parameter, validDescribers, index, source);

            scope->AddArgument(parameter);
        }
    }

    void CreateIndexerFunctions(const GetNode* const getNode, const SetNode* const setNode, const CompoundDeclarationNode* declarationNode, const std::vector<const DataType*>& parameters, const DataType* const creationType, const Describer describer, MethodFunction*& get, VoidFunction*& set, const SourceFile* const source)
    {
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

            if (set->GetArgument("value") >= 0)
                PushException(new DuplicateVariableDefinitionException("value", declarationNode->Index(), source));
            else
                set->AddArgument(new FunctionParameter("value", Describer::Const, creationType));
        }
    }

    void CreateIndexer(const BaseIndexerNode* const indexerNode, DataType* const dataType)
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

        std::vector<const DataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindIndexer(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto describer = FromNode(indexerNode->Describer());

        MethodFunction* get = nullptr; VoidFunction* set = nullptr;
        CreateIndexerFunctions(indexerNode->Get(), indexerNode->Set(), declarationNode, parameters, creationType, describer, get, set, source);

        const auto indexer = new Indexer(describer, creationType, get, set);

        MatchReturnAccessibility(indexer, index, dataType);
        ValidateDescriber(indexer, Describer::AccessModifiers, index, source);;

        dataType->PushIndexer(indexer);
    }

    void CreateFunction(const FunctionCreationNode* const functionCreationNode, DataType* const dataType)
    {
        const auto index = functionCreationNode->Index();
        const auto source = dataType->Parent();

        const auto identifier = functionCreationNode->Name()->Value();
        const auto declarationNode = functionCreationNode->Parameters();

        std::vector<const DataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindFunction(identifier, parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto describer = FromNode(functionCreationNode->Describer());

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
        ValidateDescriber(function, Describer::ValidMembers, index, source);

        dataType->PushFunction(function);
    }

    void CreateConstructor(const ConstructorCreationNode* const constructorDefinitionNode, DataType* const dataType)
    {
        const auto index = constructorDefinitionNode->Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto declarationNode = constructorDefinitionNode->Parameters();

        std::vector<const DataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindConstructor(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto constructor = new Constructor(FromNode(constructorDefinitionNode->Describer()), dataType, constructorDefinitionNode->Body());
        BindFunctionParameters(constructor, parameters, declarationNode, source);

        ValidateDescriber(constructor, Describer::AccessModifiers, index, source);

        dataType->PushConstructor(constructor);
    }

    void CreateExplict(const ExplicitCastNode* const explicitCastNode, DataType* const dataType)
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

        std::vector<const DataType*> parameters;
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
        MatchDescriber(explicitCast, Describer::Public | Describer::Static, index, source);

        dataType->PushExplicitCast(explicitCast);
    }

    void CreateImplicit(const ImplicitCastNode* const implicitCastNode, DataType* const dataType)
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

        std::vector<const DataType*> parameters;
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
        MatchDescriber(implicitCast, Describer::Public | Describer::Static, index, source);

        dataType->PushImplicitCast(implicitCast);
    }

    void CreateOperatorOverload(const OperatorOverloadNode* const operatorOverloadNode, DataType* const dataType)
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

        std::vector<const DataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        const auto& token = operatorOverloadNode->Operator();
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

        MatchDescriber(operatorOverload, Describer::Public | Describer::Static, index, source);

        dataType->PushOverload(operatorOverload);
    }

    void BindEnum(Enum* enumSource)
    {
        for (const auto child: *enumSource->Skeleton()->Body())
        {
            switch (child->NodeType())
            {
                case NodeType::Expression:
                    BindEnumExpression(dynamic_cast<const ExpressionStatementNode*>(child), enumSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Index(), enumSource->Parent()));
                    break;
            }
        }
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
                case MemberType::Struct:
                    BindStruct(dynamic_cast<StructSource*>(type));
                    break;
                default:
                    break;
            }
        }
    }
}
