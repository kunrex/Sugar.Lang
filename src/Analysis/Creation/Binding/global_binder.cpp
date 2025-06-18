#include "global_binder.h"

#include <format>

#include "binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compilation/Analysis/static_binding_exception.h"
#include "../../../Exceptions/Compilation/Analysis/variable_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/return_accessibility_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/non_static_member_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Global/duplicate_function_definition_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Local/accessor_body_exception.h"

#include "../../../Lexing/Tokens/Factories/operator.h"

#include "../../Structure/DataTypes/enum.h"
#include "../../Structure/DataTypes/class.h"

#include "../../Structure/Global/BuiltIn/built_in_cast.h"
#include "../../Structure/Global/BuiltIn/built_in_constructor.h"

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
#include "../../Structure/Wrappers/Generic/array.h"

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

    void MatchReturnAccessibility(const Indexer* const indexer, const unsigned long index, const IUserDefinedType* const dataType)
    {
        if (indexer->CreationType()->CheckDescriber(Describer::Public))
            return;

        if (indexer->CheckDescriber(Describer::Public) && dataType->CheckDescriber(Describer::Public))
            PushException(new ReturnAccessibilityException(index, dataType->Parent()));
    }

    void BindEnumConstant(const IParseNode* const expressionNode, Enum* const dataType)
    {
        switch (expressionNode->NodeType())
        {
            case NodeType::Identifier:
                {
                    const auto& identifier = expressionNode->Token();
                    const auto value = *identifier.Value<string>();

                    if (dataType->FindCharacteristic(value) != nullptr)
                    {
                        PushException(new DuplicateVariableDefinitionException(identifier.Index(), dataType->Parent()));
                        return;
                    }

                    const auto constant = new ImplicitEnumConstant(value, dataType, dataType->LastCharacteristic());

                    constant->SetParent(dataType);
                    dataType->PushCharacteristic(constant);
                }
                break;
            case NodeType::Binary:
                {
                    if (const auto& operation = expressionNode->Token(); operation.Kind() != SyntaxKind::Assignment)
                    {
                        PushException(new InvalidGlobalStatementException(operation.Index(), dataType->Parent()));
                        return;
                    }

                    const auto lhs = expressionNode->GetChild(static_cast<int>(ChildCode::LHS));
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

                    const auto constant = new GlobalConstant(value, Describer::Public | Describer::Constexpr, dataType, expressionNode->GetChild(static_cast<int>(ChildCode::RHS)));

                    constant->SetParent(dataType);
                    dataType->PushCharacteristic(constant);
                }
                break;
            default:
                PushException(new InvalidGlobalStatementException(expressionNode->Token().Index(), dataType->Parent()));
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

        if ((describer & Describer::Constexpr) == Describer::Constexpr)
        {
            PushException(new LogException("Constants must be initialised", declarationNode->Token().Index(), source));
            return;
        }

        const auto globalVariable = new GlobalVariable(value, describer == Describer::None ? Describer::Private : describer, creationType);

        MatchReturnAccessibility(globalVariable, identifier.Index(), dataType);

        ValidateStaticBinding(globalVariable, identifier.Index(), dataType);
        ValidateDescriber(globalVariable, Describer::Const | Describer::AccessModifiers | Describer::Static, identifier.Index(), source);

        globalVariable->SetParent(dataType);
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
            globalVariable = new GlobalConstant(value, describer, creationType, initialisationNode->GetChild(static_cast<int>(ChildCode::Expression)));
        else
            globalVariable = new GlobalVariable(value, describer == Describer::None ? Describer::Private : describer, creationType, initialisationNode->GetChild(static_cast<int>(ChildCode::Expression)));

        MatchReturnAccessibility(globalVariable, identifier.Index(), dataType);

        ValidateStaticBinding(globalVariable, identifier.Index(), dataType);
        ValidateDescriber(globalVariable, Describer::Const | Describer::Constexpr | Describer::AccessModifiers | Describer::Static, identifier.Index(), source);

        globalVariable->SetParent(dataType);
        dataType->PushCharacteristic(globalVariable);
    }

    void CreateAutoGeneratedProperty(const IParseNode* const propertyNode, const string& value, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto getNode = propertyNode->GetChild(static_cast<int>(ChildCode::Get));
        auto getDescriber = FromNode(getNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (getDescriber == Describer::None)
            getDescriber = describer;
        else if ((describer & Describer::Static) == Describer::Static)
            getDescriber = getDescriber | Describer::Static;

        const auto get = new GeneratedGetFunction(getDescriber, value, creationType);
        if (dataType->FindFunction(get->Name(), { }) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(getNode->Token().Index(), source));
            delete get;
            return;
        }

        get->SetParent(dataType);
        dataType->PushFunction(get);

        const auto setNode = propertyNode->GetChild(static_cast<int>(ChildCode::Set));
        auto setDescriber = FromNode(setNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (setDescriber == Describer::None)
            setDescriber = describer;
        else if ((describer & Describer::Static) == Describer::Static)
            setDescriber = setDescriber | Describer::Static;

        const auto set = new GeneratedSetFunction(setDescriber, value, creationType);
        if (dataType->FindFunction(set->Name(), { creationType }) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(getNode->Token().Index(), source));
            delete set;
            return;
        }

        set->SetParent(dataType);
        dataType->PushFunction(set);

        const auto property = new AutoImplementedProperty(value, describer, creationType, get, set, propertyNode->GetChild(static_cast<int>(ChildCode::Expression)));

        MatchReturnAccessibility(property, propertyNode->Token().Index(), dataType);

        ValidateStaticBinding(property, propertyNode->Token().Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, propertyNode->Token().Index(), source);

        property->SetParent(dataType);
        dataType->PushCharacteristic(property);
    }

    IFunction* CreatePropertyGet(const IParseNode* const getNode, const Describer describer, const std::string& value, const IDataType* const creationType, IUserDefinedType* const dataType)
    {
        auto getDescriber = FromNode(getNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (getDescriber == Describer::None)
            getDescriber = describer;
        else if ((describer & Describer::Static) == Describer::Static)
            getDescriber = getDescriber | Describer::Static;

        const auto get = new MethodFunction("__get__" + value, getDescriber, creationType, getNode->GetChild(static_cast<int>(ChildCode::Body)));
        if (dataType->FindFunction(get->Name(), { }) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(getNode->Token().Index(), dataType->Parent()));
            delete get;

            return nullptr;
        }

        get->SetParent(dataType);
        dataType->PushFunction(get);

        return get;
    }

    IFunction* CreatePropertySet(const IParseNode* const setNode, const Describer describer, const std::string& value, const IDataType* const creationType, IUserDefinedType* const dataType)
    {
        auto setDescriber = FromNode(setNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (setDescriber == Describer::None)
            setDescriber = describer;
        else if ((describer & Describer::Static) == Describer::Static)
            setDescriber = setDescriber | Describer::Static;

        const auto set = new VoidFunction("__set__" + value, setDescriber, setNode->GetChild(static_cast<int>(ChildCode::Body)));
        if (dataType->FindFunction(set->Name(), { creationType }) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(setNode->Token().Index(), dataType->Parent()));
            delete set;

            return nullptr;
        }

        set->AddParameter(new FunctionParameter("value", Describer::None, creationType));
        set->SetParent(dataType);
        dataType->PushFunction(set);

        return set;
    }

    void CreateGetProperty(const IParseNode* const propertyNode, const string& value, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto get = CreatePropertyGet(propertyNode->GetChild(static_cast<int>(ChildCode::Get)), describer, value, creationType, dataType);
        if (get == nullptr)
            return;

        const auto property = new GetProperty(value, describer, creationType, get);

        MatchReturnAccessibility(property, propertyNode->Token().Index(), dataType);

        ValidateStaticBinding(property, propertyNode->Token().Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, propertyNode->Token().Index(), source);

        property->SetParent(dataType);
        dataType->PushCharacteristic(property);
    }

    void CreateSetProperty(const IParseNode* const propertyNode, const string& value, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto set = CreatePropertySet(propertyNode->GetChild(static_cast<int>(ChildCode::Set)), describer, value, creationType, dataType);
        if (set == nullptr)
            return;

        const auto property = new SetProperty(value, describer, creationType, set);

        MatchReturnAccessibility(property, propertyNode->Token().Index(), dataType);

        ValidateStaticBinding(property, propertyNode->Token().Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, propertyNode->Token().Index(), source);

        property->SetParent(dataType);
        dataType->PushCharacteristic(property);
    }

    void CreateGetSetProperty(const IParseNode* const propertyNode, const string& value, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(propertyNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(propertyNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto get = CreatePropertyGet(propertyNode->GetChild(static_cast<int>(ChildCode::Get)), describer, value, creationType, dataType);
        if (get == nullptr)
            return;

        const auto set = CreatePropertySet(propertyNode->GetChild(static_cast<int>(ChildCode::Set)), describer, value, creationType, dataType);
        if (set == nullptr)
            return;

        const auto property = new GetSetProperty(value, describer, creationType, get, set);

        MatchReturnAccessibility(property, propertyNode->Token().Index(), dataType);

        ValidateStaticBinding(property, propertyNode->Token().Index(), dataType);
        ValidateDescriber(property, Describer::Static | Describer::AccessModifiers, propertyNode->Token().Index(), source);

        property->SetParent(dataType);
        dataType->PushCharacteristic(property);
    }

    void CreateProperty(const IParseNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto getNode = propertyNode->GetChild(static_cast<int>(ChildCode::Get));
        const auto setNode = propertyNode->GetChild(static_cast<int>(ChildCode::Set));

        if (getNode != nullptr && setNode != nullptr)
        {
            const auto getBody = getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() != NodeType::Empty;
            const auto setBody = setNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() != NodeType::Empty;

            if (getBody && setBody)
                CreateGetSetProperty(propertyNode, value, dataType);
            else  if (!getBody && !setBody)
                CreateAutoGeneratedProperty(propertyNode, value, dataType);
            else
                PushException(new LogException("Expected both accessors to define a body", identifier.Index(), source));
        }
        else if (getNode != nullptr)
        {
            if (getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty)
                PushException(new LogException("Expected get accessor to define a body", identifier.Index(), source));
            else
                CreateGetProperty(propertyNode, value, dataType);
        }
        else if (setNode != nullptr)
        {
            if (setNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty)
                PushException(new LogException("Expected set accessor to define a body", identifier.Index(), source));
            else
                CreateSetProperty(propertyNode, value, dataType);
        }
    }

    void InitialiseProperty(const IParseNode* const propertyNode, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto identifier = propertyNode->GetChild(static_cast<int>(ChildCode::Identifier))->Token();

        const auto value = *identifier.Value<string>();

        if (dataType->FindCharacteristic(value) != nullptr)
        {
            PushException(new DuplicateVariableDefinitionException(identifier.Index(), source));
            return;
        }

        const auto getNode = propertyNode->GetChild(static_cast<int>(ChildCode::Get));
        const auto setNode = propertyNode->GetChild(static_cast<int>(ChildCode::Set));

        if (getNode != nullptr && setNode != nullptr)
        {
            const auto noGetBody = getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty;
            const auto noSetBody = setNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty;

            if (noGetBody && noSetBody)
                CreateAutoGeneratedProperty(propertyNode, value, dataType);
            else
                PushException(new LogException("Initialised properties cannot define accessor bodies", identifier.Index(), source));
        }
        else
            PushException(new LogException("Only get set properties may be initialised", identifier.Index(), source));
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

    IFunction* CreateIndexerGet(const IParseNode* const getNode, const Describer describer, const IDataType* const creationType, const std::vector<const IDataType*>& parameters, const IParseNode* const declarationNode, IUserDefinedType* const dataType)
    {
        auto getDescriber = FromNode(getNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (getDescriber == Describer::None)
            getDescriber = describer;

        const auto get = new MethodFunction("__get__", getDescriber, creationType, getNode->GetChild(static_cast<int>(ChildCode::Body)));
        if (dataType->FindFunction(get->Name(), parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(getNode->Token().Index(), dataType->Parent()));
            delete get;

            return nullptr;
        }

        ValidateDescriber(get, Describer::AccessModifiers, getNode->Token().Index(), dataType->Parent());

        BindFunctionParameters(get, parameters, declarationNode, dataType->Parent());
        get->SetParent(dataType);
        dataType->PushFunction(get);

        return get;
    }

    IFunction* CreateIndexerSet(const IParseNode* const setNode, const Describer describer, const IDataType* const creationType, const std::vector<const IDataType*>& parameters, const IParseNode* const declarationNode, IUserDefinedType* const dataType)
    {
        auto setDescriber = FromNode(setNode->GetChild(static_cast<int>(ChildCode::Describer)));
        if (setDescriber == Describer::None)
            setDescriber = describer;

        std::vector extended(parameters);
        extended.push_back(creationType);

        const auto set = new VoidFunction("__set__", setDescriber, setNode->GetChild(static_cast<int>(ChildCode::Body)));
        if (dataType->FindFunction(set->Name(), extended) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(setNode->Token().Index(), dataType->Parent()));
            delete set;

            return nullptr;
        }

        ValidateDescriber(set, Describer::AccessModifiers, setNode->Token().Index(), dataType->Parent());

        BindFunctionParameters(set, parameters, declarationNode, dataType->Parent());
        set->AddParameter(new LocalVariable("value", Describer::Const, creationType));

        set->SetParent(dataType);
        dataType->PushFunction(set);

        return set;
    }

    void CreateGetIndexer(const IParseNode* indexerNode, const std::vector<const IDataType*>& parameters, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(indexerNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(indexerNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto get = CreateIndexerGet(indexerNode->GetChild(static_cast<int>(ChildCode::Get)), describer, creationType, parameters, indexerNode->GetChild(static_cast<int>(ChildCode::Parameters)), dataType);
        if (get == nullptr)
            return;

        const auto indexer = new GetIndexer(describer, creationType, get);

        MatchReturnAccessibility(indexer, indexerNode->Token().Index(), dataType);
        ValidateDescriber(indexer, Describer::AccessModifiers, indexerNode->Token().Index(), source);

        indexer->SetParent(dataType);
        dataType->PushIndexer(indexer);
    }

    void CreateSetIndexer(const IParseNode* indexerNode, const std::vector<const IDataType*>& parameters, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto creationType = BindDataType(indexerNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(indexerNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto set = CreateIndexerSet(indexerNode->GetChild(static_cast<int>(ChildCode::Set)), describer, creationType, parameters, indexerNode->GetChild(static_cast<int>(ChildCode::Parameters)), dataType);
        if (set == nullptr)
            return;

        const auto indexer = new SetIndexer(describer, creationType, set);

        MatchReturnAccessibility(indexer, indexerNode->Token().Index(), dataType);
        ValidateDescriber(indexer, Describer::AccessModifiers, indexerNode->Token().Index(), source);

        indexer->SetParent(dataType);
        dataType->PushIndexer(indexer);
    }

    void CreateGetSetIndexer(const IParseNode* indexerNode, const std::vector<const IDataType*>& parameters, IUserDefinedType* const dataType)
    {
        const auto source = dataType->Parent();

        const auto declarationNode = indexerNode->GetChild(static_cast<int>(ChildCode::Parameters));
        const auto creationType = BindDataType(indexerNode->GetChild(static_cast<int>(ChildCode::Type)), source);

        const auto provided = FromNode(indexerNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        const auto get = CreateIndexerGet(indexerNode->GetChild(static_cast<int>(ChildCode::Get)), describer, creationType, parameters, declarationNode, dataType);
        if (get == nullptr)
            return;

        const auto set = CreateIndexerSet(indexerNode->GetChild(static_cast<int>(ChildCode::Set)), describer, creationType, parameters, declarationNode, dataType);
        if (set == nullptr)
            return;

        const auto indexer = new GetSetIndexer(describer, creationType, get, set);

        MatchReturnAccessibility(indexer, indexerNode->Token().Index(), dataType);
        ValidateDescriber(indexer, Describer::AccessModifiers, indexerNode->Token().Index(), source);

        indexer->SetParent(dataType);
        dataType->PushIndexer(indexer);
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

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(indexerNode->GetChild(static_cast<int>(ChildCode::Parameters)), parameters, source);

        if (dataType->FindIndexer(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto getNode = indexerNode->GetChild(static_cast<int>(ChildCode::Get));
        const auto setNode = indexerNode->GetChild(static_cast<int>(ChildCode::Set));

        if (getNode == nullptr)
        {
            if (setNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty)
                PushException(new LogException("Expected set accessor to define a body", setNode->Token().Index(), source));
            else
                CreateSetIndexer(indexerNode, parameters, dataType);
        }
        else if (setNode == nullptr)
        {
            if (getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() == NodeType::Empty)
                PushException(new LogException("Expected get accessor to define a body", getNode->Token().Index(), source));
            else
                CreateGetIndexer(indexerNode, parameters, dataType);
        }
        else
        {
            const auto getBody = getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() != NodeType::Empty;
            const auto setBody = getNode->GetChild(static_cast<int>(ChildCode::Body))->NodeType() != NodeType::Empty;

            if (getBody && setBody)
                CreateGetSetIndexer(indexerNode, parameters, dataType);
            else
                PushException(new LogException("Expected both accessors to define a body", getNode->Token().Index(), source));
        }
    }

    Entrypoint* DefineEntrypoint(const IParseNode* const functionCreationNode, const string& value, const Describer describer, IUserDefinedType* const dataType)
    {
        if (Entrypoint::Instance() != nullptr)
        {
            PushException(new LogException("Entrypoint is already defined", functionCreationNode->Token().Index(), dataType->Parent()));
            return nullptr;
        }

        if (const auto typeNode = functionCreationNode->GetChild(static_cast<int>(ChildCode::Type)); typeNode->NodeType() != NodeType::VoidType)
        {
            PushException(new LogException("Entrypoint must be a void function", functionCreationNode->Token().Index(), dataType->Parent()));
            return nullptr;
        }

        if (describer != Describer::Entrypoint)
            PushException(new InvalidDescriberException(describer, Describer::Entrypoint, functionCreationNode->Token().Index(), dataType->Parent()));

        const auto entryPoint = Entrypoint::InitInstance(value, describer, functionCreationNode->GetChild(static_cast<int>(ChildCode::Body)));

        entryPoint->SetParent(dataType);
        dataType->PushFunction(entryPoint);

        return entryPoint;
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

        if ((describer & Describer::Entrypoint) == Describer::Entrypoint)
        {
            if (const auto entryPoint = DefineEntrypoint(functionCreationNode, value, describer, dataType); entryPoint != nullptr)
            {
                BindFunctionParameters(entryPoint, parameters, declarationNode, source);

                if (parameters.size() > 1)
                    PushException(new LogException("Entrypoint can define no parameters or one parameter of array<string>", identifier.Index(), source));
                else if (parameters.size() == 1 && parameters[0] != Array::Instance(String::Instance()))
                    PushException(new LogException("Expected type of array<string>", identifier.Index(), source));
            }

            return;
        }

        FunctionDefinition* function;
        if (const auto typeNode = functionCreationNode->GetChild(static_cast<int>(ChildCode::Type)); typeNode->NodeType() == NodeType::VoidType)
        {
            const auto voidDefinition = new VoidFunction(value, describer, functionCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(voidDefinition, parameters, declarationNode, source);

            voidDefinition->SetParent(dataType);
            function = voidDefinition;
        }
        else
        {
            const auto methodDefinition = new MethodFunction(value, describer, BindDataType(typeNode, source), functionCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
            BindFunctionParameters(methodDefinition, parameters, declarationNode, source);

            methodDefinition->SetParent(dataType);
            function = methodDefinition;

            MatchReturnAccessibility(function, identifier.Index(), dataType);
        }

        ValidateStaticBinding(function, identifier.Index(), dataType);
        ValidateDescriber(function, Describer::Static | Describer::AccessModifiers, identifier.Index(), source);

        dataType->PushFunction(function);
    }

    void CreateStaticConstructor(const IParseNode* const constructorCreationNode, const Describer describer, IUserDefinedType* const dataType)
    {
        const auto index = constructorCreationNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->StaticConstructor() != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto constructor = new StaticDefinedConstructor(dataType, constructorCreationNode->GetChild(static_cast<int>(ChildCode::Body)));

        if (describer != (Describer::Private | Describer::Static))
            PushException(new LogException("Static constructor must be private static only", index, source));

        constructor->SetParent(dataType);
        dataType->PushConstructor(constructor);
    }

    void CreateInstanceConstructor(const IParseNode* const constructorCreationNode, const Describer describer, IUserDefinedType* const dataType)
    {
        const auto index = constructorCreationNode->Token().Index();
        const auto source = dataType->Parent();

        if (dataType->InstanceConstructor() != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto constructor = new DefinedConstructor(describer, dataType, constructorCreationNode->GetChild(static_cast<int>(ChildCode::Body)));

        ValidateDescriber(constructor, Describer::AccessModifiers, index, source);

        constructor->SetParent(dataType);
        dataType->PushConstructor(constructor);
    }

    void CreateConstructor(const IParseNode* const constructorCreationNode, IUserDefinedType* const dataType)
    {
        const auto index = constructorCreationNode->Token().Index();
        const auto source = dataType->Parent();

        const auto declarationNode = constructorCreationNode->GetChild(static_cast<int>(ChildCode::Parameters));

        std::vector<const IDataType*> parameters;
        BindFunctionParameters(declarationNode, parameters, source);

        const auto provided = FromNode(constructorCreationNode->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto describer = provided == Describer::None ? Describer::Private : provided;

        if ((describer & Describer::Static) == Describer::Static)
        {
            if (!parameters.empty())
                PushException(new LogException("Static constructor cannot define parameters", index, source));

            CreateStaticConstructor(constructorCreationNode, describer, dataType);
            return;
        }

        if (parameters.empty())
        {
            CreateInstanceConstructor(constructorCreationNode, describer, dataType);
            return;
        }

        if (dataType->FindConstructor(parameters) != nullptr)
        {
            PushException(new DuplicateFunctionDefinition(index, source));
            return;
        }

        const auto constructor = new Constructor(describer, dataType, constructorCreationNode->GetChild(static_cast<int>(ChildCode::Body)));
        BindFunctionParameters(constructor, parameters, declarationNode, source);

        ValidateDescriber(constructor, Describer::AccessModifiers, index, source);

        constructor->SetParent(dataType);
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

        explicitCast->SetParent(dataType);
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

        implicitCast->SetParent(dataType);
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

        const auto declarationNode = operatorOverloadNode->GetChild(static_cast<int>(ChildCode::Parameters));

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

        operatorOverload->SetParent(dataType);
        dataType->PushOverload(operatorOverload);
    }

    void TryDeclareExplicitString(IUserDefinedType* const dataType)
    {
        if (dataType->FindExplicitCast(String::Instance(), dataType) != nullptr)
            return;

        const auto cast = new BuiltInCast(String::Instance(), std::format("call instance string class {}::ToString()", dataType->FullName()), nullptr);
        cast->PushParameterType(dataType);
        dataType->PushExplicitCast(cast);
    }

    void TryDeclareStaticConstructor(IUserDefinedType* const dataType)
    {
        if (dataType->StaticConstructor() != nullptr)
            return;

        const auto constructor = new StaticImplicitConstructor(dataType);

        constructor->SetParent(dataType);
        dataType->PushConstructor(constructor);
    }

    void TryDeclareInstanceConstructor(IUserDefinedType* const dataType)
    {
        if (dataType->InstanceConstructor() != nullptr)
            return;

        const auto constructor = new ImplicitConstructor(Describer::Public, dataType);

        constructor->SetParent(dataType);
        dataType->PushConstructor(constructor);
    }
}
