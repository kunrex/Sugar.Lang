#include "global_binder.h"

#include <format>

#include "binder_extensions.h"
#include "../../../Exceptions/exception_manager.h"

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

#include "../../Structure/Wrappers/Value/integer.h"

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

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Groups;
using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Properties;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;
using namespace ParseNodes::Functions::Creation;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::DataTypes;

constexpr std::string_view get_property_name = "get_item";
constexpr std::string_view set_property_name = "set_item";

constexpr std::string_view get_indexer_name = "get_indexer";
constexpr std::string_view set_indexer_name = "set_indexer";

namespace Analysis::Creation::Binding
{
    void MatchReturnAccessibility(const Characteristic* const characteristic, const DataType* const dataType)
    {
        if (characteristic->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (characteristic->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
        {
            //exception
        }
    }

    void MatchReturnAccessibility(const Function* const function, const DataType* const dataType)
    {
        if (function->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (function->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
        {
            //exception
        }
    }

    void MatchReturnAccessibility(const Structure::Creation::IndexerDefinition* const indexer, const DataType* const dataType)
    {
        if (indexer->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (indexer->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
        {
            //exception
        }
    }

    void BindEnumExpression(const ExpressionStatementNode* const expressionNode, DataType* const dataType)
    {
        switch (const auto expression = expressionNode->Expression(); expression->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto identifier = dynamic_cast<const IdentifierNode*>(expression);
                    if (dataType->FindCharacteristic(identifier->Value()) != nullptr)
                    {
                        //exception
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalVariable(identifier->Value(), Describer::Public | Describer::Const, &Integer::Instance()));
                }
                break;
            case NodeType::Binary:
                {
                    const auto casted = dynamic_cast<const BinaryNode*>(expression);
                    if (casted->Base().Kind() != SyntaxKind::Assignment)
                    {
                        //exception
                        return;
                    }

                    const auto lhs = casted->LHS();
                    if (lhs->NodeType() != NodeType::Identifier)
                    {
                        //exception
                        return;
                    }

                    const auto identifier = dynamic_cast<const IdentifierNode*>(lhs);
                    if (dataType->FindCharacteristic(identifier->Value()) != nullptr)
                    {
                        //exception
                        return;
                    }

                    dataType->PushCharacteristic(new GlobalVariable(identifier->Value(), Describer::Public | Describer::Const, &Integer::Instance(), casted->RHS()));
                }
                break;
            default:
                //exception
                break;
        }
    }

    void DeclareGlobalVariable(const DeclarationNode* const declarationNode, DataType* const dataType)
    {
        const auto identifier = declarationNode->Name()->Value();
        const auto creationType = BindDataType(declarationNode->Type(), dataType->Parent());

        if (creationType == nullptr)
        {
            //exception
            return;
        }

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(declarationNode->Describer());
        const auto globalVariable = new GlobalVariable(identifier, describer, creationType);

        dataType->PushCharacteristic(globalVariable);
        MatchStaticBindings(globalVariable, dataType, declarationNode->Index());
        MatchReturnAccessibility(globalVariable, dataType);
    }

    void InitialiseGlobalVariable(const InitialisationNode* const initialisationNode, DataType* const dataType)
    {
        const auto identifier = initialisationNode->Name()->Value();
        const auto creationType = BindDataType(initialisationNode->Type(), dataType->Parent());

        if (creationType == nullptr)
        {
            //exception
            return;
        }

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(initialisationNode->Describer());
        const auto globalVariable = new GlobalVariable(identifier, describer, creationType, initialisationNode->Value());

        dataType->PushCharacteristic(globalVariable);
        MatchStaticBindings(globalVariable, dataType, initialisationNode->Index());
        MatchReturnAccessibility(globalVariable, dataType);
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
        const auto identifier = propertyNode->Name()->Value();
        const auto creationType = BindDataType(propertyNode->Type(), dataType->Parent());

        if (creationType == nullptr)
        {
            //exception
            return;
        }

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(propertyNode->Describer());

        const MethodFunction* get = nullptr;
        VoidFunction* set = nullptr;
        CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, describer, creationType, get, set);
        const auto property = new Property(identifier, describer, creationType, get, set);

        dataType->PushCharacteristic(property);
        MatchStaticBindings(property, dataType, propertyNode->Index());
        MatchReturnAccessibility(property, dataType);
    }

    void InitialiseProperty(const AssignedPropertyNode* const propertyNode, DataType* const dataType)
    {
        const auto identifier = propertyNode->Name()->Value();
        const auto creationType = BindDataType(propertyNode->Type(), dataType->Parent());

        if (creationType == nullptr)
        {
            //exception
            return;
        }

        if (dataType->FindCharacteristic(identifier) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(propertyNode->Describer());

        const MethodFunction* get = nullptr;
        VoidFunction* set = nullptr;
        CreatePropertyFunctions(propertyNode->Get(), propertyNode->Set(), identifier, describer, creationType, get, set);
        const auto property = new Property(identifier, describer, creationType, get, set, propertyNode->Value());

        dataType->PushCharacteristic(property);
        MatchStaticBindings(property, dataType, propertyNode->Index());
        MatchReturnAccessibility(property, dataType);
    }

    void BindFunctionParameters(Scoped* const scope, const std::vector<const DataType*>& parameters, const CompoundDeclarationNode* const declarationNode)
    {
        for (int i = 0; i < declarationNode->ChildCount(); ++i)
        {
            const auto current = declarationNode->GetChild(i);
            const auto name = current->Name()->Value();

            if (scope->ContainsArgument(name))
            {
                //exception
            }

            const auto describer = FromNode(current->Describer());

            const auto parameter = new FunctionParameter(name, describer, parameters.at(i));
            if (!parameter->ValidateDescriber(Describer::Ref | Describer::Const))
            {
                //exception
            }

            scope->AddArgument(parameter);
        }
    }

    void CreateIndexerFunctions(const GetNode* const getNode, const SetNode* const setNode, const CompoundDeclarationNode* declarationNode, const std::vector<const DataType*>& parameters, const DataType* const creationType, const Describer describer, MethodFunction*& get, VoidFunction*& set)
    {
        if (getNode != nullptr)
        {
            const auto actualDescriber = (FromNode(getNode->Describer()) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            get = new MethodFunction(std::string(get_indexer_name), actualDescriber, creationType, getNode->Body());
            BindFunctionParameters(get, parameters, declarationNode);
        }

        if (setNode != nullptr)
        {
            const auto actualDescriber = (FromNode(setNode->Describer()) & describer & Describer::Public) == Describer::Public ? Describer::Public : Describer::Private;

            set = new VoidFunction(std::string(set_indexer_name), actualDescriber, setNode->Body());
            BindFunctionParameters(set, parameters, declarationNode);
            if (set->GetArgument("value") >= 0)
            {
                //exception
            }
            else
                set->AddArgument(new FunctionParameter("value", Describer::Const, creationType));
        }
    }

    void CreateIndexer(const BaseIndexerNode* const indexerNode, DataType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static))
        {
            //exception
            return;
        }

        const auto creationType = BindDataType(indexerNode->Type(), dataType->Parent());
        const auto declarationNOde = indexerNode->Parameters();

        std::vector<const DataType*> parameters;
        for (const auto typeNode: *declarationNOde)
        {
            const auto type = BindDataType(typeNode->Type(), dataType->Parent());
            if (type == nullptr)
            {
                //exception
                return;
            }

            parameters.push_back(type);
        }

        if (dataType->FindIndexer(parameters) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(indexerNode->Describer());
        if ((describer & Describer::Static) == Describer::Static)
        {
            //exception
        }

        MethodFunction* get = nullptr;
        VoidFunction* set = nullptr;
        CreateIndexerFunctions(indexerNode->Get(), indexerNode->Set(), declarationNOde, parameters, creationType, describer, get, set);

        const auto indexer = new Indexer(describer, creationType, get, set);
        dataType->PushIndexer(indexer);
        MatchReturnAccessibility(indexer, dataType);
    }

    void CreateFunction(const FunctionCreationNode* const functionCreation, DataType* const dataType)
    {
        const auto identifier = functionCreation->Name()->Value();

        std::vector<const DataType*> parameters;
        for (const auto typeNode: *functionCreation->Parameters())
        {
            const auto type = BindDataType(typeNode->Type(), dataType->Parent());
            if (type == nullptr)
            {
                //exception
                return;
            }

            parameters.push_back(type);
        }

        if (dataType->FindFunction(identifier, parameters) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(functionCreation->Describer());

        if (const auto typeNode = functionCreation->Type(); typeNode->NodeType() == NodeType::VoidType)
        {
            const auto function = new VoidFunction(identifier, describer, functionCreation->Body());
            BindFunctionParameters(function, parameters, functionCreation->Parameters());;

            dataType->PushFunction(function);
            MatchStaticBindings(function, dataType, functionCreation->Index());
            MatchReturnAccessibility(function, dataType);
        }
        else
        {
            const auto function = new MethodFunction(identifier, describer, BindDataType(typeNode, dataType->Parent()), functionCreation->Body());
            BindFunctionParameters(function, parameters, functionCreation->Parameters());;

            dataType->PushFunction(function);
            MatchStaticBindings(function, dataType, functionCreation->Index());
            MatchReturnAccessibility(function, dataType);
        }
    }

    void CreateConstructor(const ConstructorCreationNode* const constructor, DataType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static))
        {
            //exception
            return;
        }

        std::vector<const DataType*> parameters;
        for (const auto typeNode: *constructor->Parameters())
        {
            const auto type = BindDataType(typeNode->Type(), dataType->Parent());
            if (type == nullptr)
            {
                //exception
                return;
            }

            parameters.push_back(type);
        }

        if (dataType->FindConstructor(parameters) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(constructor->Describer());
        if ((describer & Describer::Static) == Describer::Static)
        {
            //exception
        }

        const auto constructorDefinition = new Constructor(describer, dataType, constructor->Body());
        BindFunctionParameters(constructorDefinition, parameters, constructor->Parameters());

        dataType->PushConstructor(constructorDefinition);
    }

    void CreateExplict(const ExplicitCastNode* const explicitCast, DataType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static))
        {
            //exception
            return;
        }

        const auto creationType = BindDataType(explicitCast->Type(), dataType->Parent());
        if (creationType == nullptr)
        {
            //exception
            return;
        }

        const auto parameters = explicitCast->Parameters();
        if (parameters->ChildCount() != 1)
        {
            //exception
            return;
        }

        const auto fromTypeNode = parameters->GetChild(0);
        const auto fromType = BindDataType(fromTypeNode->Type(), dataType->Parent());
        if (fromType == nullptr)
        {
            //exception
            return;
        }

        if (fromType != dataType && creationType != dataType)
        {
            //exception
            return;
        }

        if  (dataType->FindExplicitCast(creationType, fromType) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(explicitCast->Describer());
        if (describer != Describer::PublicStatic)
        {
            //exception
        }

        const auto explicitCastDefinition = new ExplicitCast(describer, creationType, explicitCast->Body());

        const auto argument = new FunctionParameter(fromTypeNode->Name()->Value(), FromNode(explicitCast->Describer()), fromType);
        if (!argument->ValidateDescriber(Describer::Const))
        {
            //exception
        }

        explicitCastDefinition->AddArgument(argument);
        dataType->PushExplicitCast(explicitCastDefinition);
        MatchReturnAccessibility(explicitCastDefinition, dataType);
    }

    void CreateImplicit(const ImplicitCastNode* const implicitCast, DataType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static))
        {
            //exception
            return;
        }

        const auto creationType = BindDataType(implicitCast->Type(), dataType->Parent());
        if (creationType == nullptr)
        {
            //exception
            return;
        }

        const auto parameters = implicitCast->Parameters();
        if (parameters->ChildCount() != 1)
        {
            //exception
            return;
        }

        const auto fromTypeNode = parameters->GetChild(0);
        const auto fromType = BindDataType(fromTypeNode->Type(), dataType->Parent());
        if (fromType == nullptr)
        {
            //exception
            return;
        }

        if (fromType != dataType && creationType != dataType)
        {
            //exception
            return;
        }

        if  (dataType->FindImplicitCast(creationType, fromType) != nullptr)
        {
            //exception
            return;
        }

        const auto describer = FromNode(implicitCast->Describer());
        if (describer != Describer::PublicStatic)
        {
            //exception
        }

        const auto implicitCastDefinition = new ImplicitCast(describer, creationType, implicitCast->Body());

        const auto argument = new FunctionParameter(fromTypeNode->Name()->Value(), FromNode(implicitCast->Describer()), fromType);
        if (!argument->ValidateDescriber(Describer::Const))
        {
            //exception
        }

        implicitCastDefinition->AddArgument(argument);
        dataType->PushImplicitCast(implicitCastDefinition);
        MatchReturnAccessibility(implicitCastDefinition, dataType);
    }

    void CreateOperator(const OperatorOverloadNode* const operatorOverload, DataType* const dataType)
    {
        if (dataType->CheckDescriber(Describer::Static))
        {
            //exception
            return;
        }

        const auto creationType = BindDataType(operatorOverload->Type(), dataType->Parent());

        int argCount = 0;
        std::vector<const DataType*> parameters;
        for (const auto typeNode: *operatorOverload->Parameters())
        {
            if (BindDataType(typeNode->Type(), dataType->Parent()) != dataType)
            {
                //exception
                return;
            }

            argCount++;
            parameters.push_back(dataType);
        }

        const auto& token = operatorOverload->Operator();;
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
                    if (argCount != 1)
                    {
                        //exception
                        return;
                    }
                }
                break;
            default:
                if (argCount != 2)
                {
                    //exception
                    return;
                }
        }

        const auto describer = FromNode(operatorOverload->Describer());
        if (describer != Describer::PublicStatic)
        {
            //exception
        }

        const auto overload = new OperatorOverload(token.Kind(), describer, creationType, operatorOverload->Body());
        BindFunctionParameters(overload, parameters, operatorOverload->Parameters());

        dataType->PushOverload(overload);
        MatchReturnAccessibility(overload, dataType);
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
                    //exception
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
                    CreateOperator(dynamic_cast<const OperatorOverloadNode*>(child), classSource);
                    break;
                default:
                    //exception
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
                    CreateOperator(dynamic_cast<const OperatorOverloadNode*>(child), structSource);
                    break;
                default:
                    //exception
                        break;
            }
        }
    }

    void GlobalBindSourceFile(const Structure::SourceFile* const source)
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
                case NodeType::Import:
                    break;
                default:
                    //exception
                    break;
            }
        }
    }
}
