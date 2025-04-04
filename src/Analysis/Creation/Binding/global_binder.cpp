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

using namespace std;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

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

    void BindEnumExpression(const IParseNode* const expression, IUserDefinedType* const dataType)
    {
        switch (expression->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto identifier = expression->GetChild(static_cast<int>(ChildCode::Identifier))->Token();
                    const auto value = *identifier.Value<string>();

                    if (dataType->FindCharacteristic(value) != nullptr)
                    {
                        PushException(new DuplicateVariableDefinitionException(identifier.Index(), dataType->Parent()));
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalConstant(value, Describer::Public | Describer::Constexpr, &Integer::Instance(), nullptr));
                }
                break;
            case NodeType::Binary:
                {
                    const auto operation = expression->Token();

                    if (operation.Kind() != SyntaxKind::Assignment)
                    {
                        PushException(new InvalidGlobalStatementException(operation.Index(), dataType->Parent()));
                        return;
                    }

                    const auto lhs = expression->GetChild(static_cast<int>(ChildCode::LHS));
                    if (lhs->NodeType() != NodeType::Identifier)
                    {
                        PushException(new InvalidGlobalStatementException(lhs->Token().Index(), dataType->Parent()));
                        return;
                    }

                    const auto identifier = lhs->Token();
                    const auto value = *identifier.Value<string>();
                    if (dataType->FindCharacteristic(value) != nullptr)
                    {
                        PushException(new DuplicateVariableDefinitionException(identifier.Index(), dataType->Parent()));
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalConstant(value, Describer::Public | Describer::Constexpr, &Integer::Instance(), expression->GetChild(static_cast<int>(ChildCode::RHS))));
                }
                break;
            default:
                PushException(new InvalidGlobalStatementException(expression->Token().Index(), dataType->Parent()));
                break;
        }
    }

    void DeclareGlobalVariable(const IParseNode* const declarationNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = declarationNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();
        const auto creationType = BindDataType(declarationNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto describer = FromNode(declarationNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto globalVariable = new GlobalVariable(value, describer == Describer::None ? Describer::Private : describer, creationType);

        MatchReturnAccessibility(globalVariable, identifier.Index(), dataType);

        ValidateStaticBinding(globalVariable, identifier.Index(), dataType);
        ValidateDescriber(globalVariable, Describer::AccessModifiers | Describer::Static, identifier.Index(), source);

        dataType->PushCharacteristic(globalVariable);
    }

    void InitialiseGlobalVariable(const IParseNode* const initialisationNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = initialisationNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();
        const auto creationType = BindDataType(initialisationNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto describer = FromNode(initialisationNode->GetChild(static_cast<int>(ChildCode::Describer)));

        GlobalVariable* globalVariable;
        if ((describer & Describer::Constexpr) == Describer::Constexpr)
            globalVariable = new GlobalConstant(value, describer == Describer::None ? Describer::Private : describer, creationType, initialisationNode->GetChild(static_cast<int>(ChildCode::Expression)));
        else
            globalVariable = new GlobalVariable(value, describer == Describer::None ? Describer::Private : describer, creationType, initialisationNode->GetChild(static_cast<int>(ChildCode::Expression)));

        MatchReturnAccessibility(globalVariable, identifier.Index(), dataType);

        ValidateStaticBinding(globalVariable, identifier.Index(), dataType);
        ValidateDescriber(globalVariable, Describer::Constexpr | Describer::AccessModifiers | Describer::Static, identifier.Index(), source);

        dataType->PushCharacteristic(globalVariable);
    }

    std::tuple<MethodDefinition*, VoidDefinition*> CreatePropertyFunctions(const IParseNode* const getNode, const IParseNode* const setNode, const std::string& identifier, const Describer describer, const IDataType* const creationType)
    {
        MethodFunction* get; VoidFunction* set;

        if (getNode != nullptr)
        {
            const auto getName = std::format("{}_{}", get_property_name, identifier);
            const auto getDescriber = FromNode(getNode->GetChild(static_cast<int>(ChildCode::Describer)));

            auto actualDescriber = (getDescriber & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;
            if ((describer & Describer::Static) == Describer::Static)
                actualDescriber = actualDescriber | Describer::Static;

            get = new MethodFunction(getName, actualDescriber, creationType, getNode->GetChild(static_cast<int>(ChildCode::Body)));
        }

        if (setNode != nullptr)
        {
            const auto setName  = std::format("{}_{}", set_property_name, identifier);
            const auto setDescriber = FromNode(setNode->GetChild(static_cast<int>(ChildCode::Describer)));

            auto actualDescriber = (setDescriber & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            if ((describer & Describer::Static) == Describer::Static)
                actualDescriber = actualDescriber | Describer::Static;

            set = new VoidFunction(setName, actualDescriber, setNode->GetChild(static_cast<int>(ChildCode::Body)));
            set->AddParameter(new FunctionParameter("value", Describer::None, creationType));
        }

        return std::make_tuple(get, set);
    }

    void CreateProperty(const IParseNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();
        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result =  CreatePropertyFunctions(propertyNode->GetChild(static_cast<int>(ChildCode::Get)), propertyNode->GetChild(static_cast<int>(ChildCode::Set)), value, actual, creationType);
        const auto property = new Property(value, actual, creationType, std::get<0>(result), std::get<1>(result));

        MatchReturnAccessibility(property, identifier.Index(), dataType);

        ValidateStaticBinding(property, identifier.Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, identifier.Index(), source);

        dataType->PushCharacteristic(property);
    }

    void InitialiseProperty(const IParseNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();
        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result =  CreatePropertyFunctions(propertyNode->GetChild(static_cast<int>(ChildCode::Get)), propertyNode->GetChild(static_cast<int>(ChildCode::Set)), value, actual, creationType);
        const auto property = new Property(value, actual, creationType, std::get<0>(result), std::get<1>(result), propertyNode->GetChild(static_cast<int>(ChildCode::Expression)));

        MatchReturnAccessibility(property, identifier.Index(), dataType);

        ValidateStaticBinding(property, identifier.Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, identifier.Index(), source);

        dataType->PushCharacteristic(property);
    }

    void BindFunctionParameters(const IParseNode* const declarationNode, std::vector<const IDataType*>& parameters, const SourceFile* const source)
    {
        const auto count = declarationNode->ChildCount();
        for (auto i = 0; i < count; ++i)
            parameters.push_back(BindDataType(declarationNode->GetChild(i)->GetChild(static_cast<int>(ChildCode::Type)), source));
    }

    void BindFunctionParameters(IScoped* const scope, const std::vector<const IDataType*>& parameters, const IParseNode* const declarationNode, const SourceFile* const source)
    {
        const auto count = declarationNode->ChildCount();
        for (int i = 0; i < count; i++)
        {
            const auto current = declarationNode->GetChild(i);

            const auto identifier = current->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

            const auto value = *identifier.Value<string>();
            const auto creationType = parameters.at(i);

            if (scope->GetParameterIndex(value))
            {
                PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
                continue;
            }

            const auto parameter = new FunctionParameter(value, FromNode(current->GetChild(static_cast<int>(ChildCode::Describer))), creationType);
            ValidateDescriber(parameter, creationType->MemberType() == MemberType::Class ? Describer::None : Describer::Ref, identifier.Index(), source);

            scope->AddParameter(parameter);
        }
    }

    std::tuple<MethodDefinition*, VoidDefinition*> CreateIndexerFunctions(const IParseNode* const getNode, const IParseNode* const setNode, const IParseNode* declarationNode, const std::vector<const IDataType*>& parameters, const IDataType* const creationType, const Describer describer, const SourceFile* const source)
    {
        MethodFunction* get; VoidFunction* set;

        if (getNode != nullptr)
        {
            const auto actualDescriber = (FromNode(getNode->GetChild(static_cast<int>(ChildCode::Describer))) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            get = new MethodFunction(std::string(get_indexer_name), actualDescriber, creationType, getNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(get, parameters, declarationNode, source);
        }

        if (setNode != nullptr)
        {
            const auto actualDescriber = (FromNode(setNode->GetChild(static_cast<int>(ChildCode::Describer))) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            set = new VoidFunction(std::string(set_indexer_name), actualDescriber, setNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(set, parameters, declarationNode, source);

            if (set->GetParameterIndex("value"))
                PushException(new DuplicateVariableDefinitionException(declarationNode->Token().Index(), source));
            else
                set->AddParameter(new FunctionParameter("value", Describer::None, creationType));
        }

        return std::make_tuple(get, set);
    }

    void CreateIndexer(const IParseNode* const indexerNode, IUserDefinedType* const dataType)
    {
        const auto index = indexerNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(indexerNode->GetChild(static_cast<int>(ChildCode::Type)), source);
        const auto declarationNode = indexerNode->GetChild(static_cast<int>(ChildCode::Parameters));

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindIndexer(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto provided = FromNode(indexerNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto actual = provided == Describer::None ? Describer::Private : provided;

        const auto result = CreateIndexerFunctions(indexerNode->GetChild(static_cast<int>(ChildCode::Get)), indexerNode->GetChild(static_cast<int>(ChildCode::Set)), declarationNode, parameters, creationType, actual, source);
        const auto indexer = new Indexer(actual, creationType, std::get<0>(result), std::get<1>(result));

        if (!creationType->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public) && indexer->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, source));

        ValidateDescriber(indexer, Describer::AccessModifiers, index, source);

        dataType->PushIndexer(indexer);
    }

    void CreateFunction(const IParseNode* const functionCreationNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = functionCreationNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();
        const auto declarationNode = functionCreationNode->GetChild(static_cast<int>(ChildCode::Parameters));

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindFunction(value, parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(identifier.Index(), source));
            return;
        }

        const auto provided = FromNode(functionCreationNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        FunctionDefinition* function;
        if (const auto typeNode = functionCreationNode->GetChild(static_cast<int>(ChildCode::Type)); typeNode->NodeType() == NodeType::VoidType)
        {
            const auto voidDefinition = new VoidFunction(value, describer, functionCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(voidDefinition, parameters, declarationNode, source);

            function = voidDefinition;
        }
        else
        {
            const auto methodDefinition = new MethodFunction(value, describer, BindDataType(typeNode, source), functionCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(methodDefinition, parameters, declarationNode, source);

            function = methodDefinition;
        }

        MatchReturnAccessibility(function, identifier.Index(), dataType);

        ValidateStaticBinding(function, identifier.Index(), dataType);
        ValidateDescriber(function, Describer::Static | Describer::AccessModifiers, identifier.Index(), source);

        dataType->PushFunction(function);
    }

    void CreateConstructor(const IParseNode* const constructorCreationNode, IUserDefinedType* const dataType)
    {
        const auto index = constructorCreationNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto declarationNode = constructorCreationNode->GetChild(static_cast<int>(ChildCode::Parameters));

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        if (dataType->FindConstructor(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto provided = FromNode(constructorCreationNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto constructor = new Constructor(describer, dataType, constructorCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
        BindFunctionParameters(constructor, parameters, declarationNode, source);

        ValidateDescriber(constructor, Describer::AccessModifiers, index, source);

        dataType->PushConstructor(constructor);
    }

    void CreateExplict(const IParseNode* const explicitCastNode, IUserDefinedType* const dataType)
    {
        const auto index = explicitCastNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(explicitCastNode->GetChild(static_cast<int>(ChildCode::Type)), source);
        const auto declarationNode = explicitCastNode->GetChild(static_cast<int>(ChildCode::Parameters));

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

        const auto explicitCast = new ExplicitCast(FromNode(explicitCastNode->GetChild(static_cast<int>(ChildCode::Describer))), creationType, explicitCastNode->GetChild(static_cast<int>(ChildCode::Body)));
        BindFunctionParameters(explicitCast, parameters, declarationNode, source);

        MatchReturnAccessibility(explicitCast, index, dataType);

        if (!explicitCast->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, index, source));

        dataType->PushExplicitCast(explicitCast);
    }

    void CreateImplicit(const IParseNode* const implicitCastNode, IUserDefinedType* const dataType)
    {
        const auto index = implicitCastNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(index, source));
            return;
        }

        const auto creationType = BindDataType(implicitCastNode->GetChild(static_cast<int>(ChildCode::Type)), source);
        const auto declarationNode = implicitCastNode->GetChild(static_cast<int>(ChildCode::Parameters));

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

        const auto implicitCast = new ImplicitCast(FromNode(implicitCastNode->GetChild(static_cast<int>(ChildCode::Describer))), creationType, implicitCastNode->GetChild(static_cast<int>(ChildCode::Body)));
        BindFunctionParameters(implicitCast, parameters, declarationNode, source);

        MatchReturnAccessibility(implicitCast, index, dataType);

        if (!implicitCast->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, index, source));

        dataType->PushImplicitCast(implicitCast);
    }

    void CreateOperatorOverload(const IParseNode* const operatorOverloadNode, IUserDefinedType* const dataType)
    {
        const auto& base = operatorOverloadNode->Token();
        const auto source = dataType->Parent();

        if (dataType->CheckDescriber(Describer::Static))
        {
            PushException(new NonStaticMemberDefinitionException(base.Index(), source));
            return;
        }

        const auto creationType = BindDataType(operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Type)), source);
        if (creationType != dataType)
            PushException(new LogException(std::format("Expected return type: {}.", dataType->FullName()), base.Index(), source));

        const auto declarationNode = operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Parameters))();

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);


        if ((static_cast<OperatorKind>(base.Kind()) & OperatorKind::Assignment) == OperatorKind::Assignment)
            PushException(new LogException("Cannot overload the assignment operator or any of its derivatives", base.Index(), source));

        switch (base.Kind())
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
                        PushException(new LogException(std::format("Expected 1 argument of type: {}.", dataType->FullName()), base.Index(), source));
                }
                break;
            default:
                {
                    if (parameters.size() != 2)
                        PushException(new LogException(std::format("Expected 2 arguments of type: {}.", dataType->FullName()), base.Index(), source));
                }
                break;
        }

        const auto operatorOverload = new OperatorOverload(base.Kind(), FromNode(operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Describer))), creationType, operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Body)));
        BindFunctionParameters(operatorOverload, parameters, operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Parameters)), source);

        MatchReturnAccessibility(operatorOverload, base.Index(), dataType);

        if (!operatorOverload->MatchDescriber(Describer::PublicStatic))
            PushException(new ExpectedDescriberException(Describer::PublicStatic, base.Index(), source));

        dataType->PushOverload(operatorOverload);
    }

    void BindEnum(IUserDefinedType* const enumSource)
    {
        const auto skeleton = enumSource->Skeleton();

        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
        {
            switch (const auto child = skeleton->GetChild(i); child->NodeType())
            {
                case NodeType::Expression:
                    BindEnumExpression(child, enumSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Token().Index(), enumSource->Parent()));
                    break;
            }
        }

        enumSource->PushExplicitCast(new BuiltInCast(&String::Instance(), std::format("call instance string valuetype {}::ToString()", enumSource->FullName())));
    }

    void BindClass(IUserDefinedType* const classSource)
    {
        const auto skeleton = classSource->Skeleton();

        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
        {
            switch (const auto child = skeleton->GetChild(i); child->NodeType())
            {
                case NodeType::Declaration:
                    DeclareGlobalVariable(child, classSource);
                    break;
                case NodeType::Initialisation:
                    InitialiseGlobalVariable(child, classSource);
                    break;
                case NodeType::Property:
                    CreateProperty(child, classSource);
                    break;
                case NodeType::PropertyInitialisation:
                    InitialiseProperty(child, classSource);
                    break;
                case NodeType::Indexer:
                    CreateIndexer(child, classSource);
                    break;
                case NodeType::FunctionDeclaration:
                    CreateFunction(child, classSource);
                    break;
                case NodeType::ConstructorDeclaration:
                    CreateConstructor(child, classSource);
                    break;
                case NodeType::ImplicitDeclaration:
                    CreateImplicit(child, classSource);
                    break;
                case NodeType::ExplicitDeclaration:
                    CreateExplict(child, classSource);
                    break;
                case NodeType::OperatorOverload:
                    CreateOperatorOverload(child, classSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Token().Index(), classSource->Parent()));
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

    void BindStruct(IUserDefinedType* const structSource)
    {
        const auto skeleton = structSource->Skeleton();

        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
        {
            switch (const auto child = skeleton->GetChild(i); child->NodeType())
            {
                case NodeType::Declaration:
                    DeclareGlobalVariable(child, structSource);
                    break;
                case NodeType::Initialisation:
                    InitialiseGlobalVariable(child, structSource);
                    break;
                case NodeType::Property:
                    CreateProperty(child, structSource);
                    break;
                case NodeType::PropertyInitialisation:
                    InitialiseProperty(child, structSource);
                    break;
                case NodeType::Indexer:
                    CreateIndexer(child, structSource);
                    break;
                case NodeType::FunctionDeclaration:
                    CreateFunction(child, structSource);
                    break;
                case NodeType::ConstructorDeclaration:
                    CreateConstructor(child, structSource);
                    break;
                case NodeType::ImplicitDeclaration:
                    CreateImplicit(child, structSource);
                    break;
                case NodeType::ExplicitDeclaration:
                    CreateExplict(child, structSource);
                    break;
                case NodeType::OperatorOverload:
                    CreateOperatorOverload(child, structSource);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Token().Index(), structSource->Parent()));
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
                    BindEnum(type);
                    break;
                case MemberType::Class:
                    BindClass(type);
                    break;
                case MemberType::ValueType:
                    BindStruct(type);
                    break;
                default:
                    break;
            }
        }
    }
}
