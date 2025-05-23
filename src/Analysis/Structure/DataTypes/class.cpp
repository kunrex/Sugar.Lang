#include "class.h"

#include <format>

#include "data_type_extensions.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Binding/binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    Class::Class(const string& name, const Enums::Describer describer) : DataType(name, describer)
    { }

    MemberType Class::MemberType() const { return MemberType::Class; }

    int Class::SlotCount() const { return 1; }

    BuiltInClass::BuiltInClass(const std::string& name, const Enums::Describer describer) : Class(name, describer)
    { }

    const string& BuiltInClass::FullName() const { return name; }

    void BuiltInClass::BindLocal()
    { }

    ClassSource::ClassSource(const string& name, const Enums::Describer describer, const IParseNode* skeleton) : Class(name, describer), skeleton(skeleton), fullName()
    { }

    TypeKind ClassSource::Type() const { return TypeKind::Custom; }

    const string& ClassSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void ClassSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const ICharacteristic* ClassSource::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    void ClassSource::PushFunction(IFunctionDefinition* const function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const IFunctionDefinition* ClassSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? functions.at(hash) : nullptr;
    }

    void ClassSource::PushConstructor(IFunction* const constructor)
    {
        constructors[ArgumentHash(constructor)] = constructor;
    }

    const IFunction* ClassSource::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash= ArgumentHash(argumentList);
        return constructors.contains(hash) ? constructors.at(hash) : nullptr;
    }

    void ClassSource::PushIndexer(IIndexerDefinition* const indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IIndexerDefinition* ClassSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? indexers.at(hash) : nullptr;
    }

    void ClassSource::PushImplicitCast(IFunction* const cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ClassSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? implicitCasts.at(hash) : nullptr;
    }

    void ClassSource::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ClassSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? explicitCasts.at(hash) : nullptr;
    }

    void ClassSource::PushOverload(IOperatorOverload* const overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const IOperatorOverload* ClassSource::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    void ClassSource::BindGlobal()
    {
        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
        {
            switch (const auto child = skeleton->GetChild(i); child->NodeType())
            {
                case NodeType::Declaration:
                    DeclareGlobalVariable(child, this);
                    break;
                case NodeType::Initialisation:
                    InitialiseGlobalVariable(child, this);
                    break;
                case NodeType::Property:
                    CreateProperty(child, this);
                    break;
                case NodeType::PropertyInitialisation:
                    InitialiseProperty(child, this);
                    break;
                case NodeType::Indexer:
                    CreateIndexer(child, this);
                    break;
                case NodeType::FunctionDeclaration:
                    CreateFunction(child, this);
                    break;
                case NodeType::ConstructorDeclaration:
                    CreateConstructor(child, this);
                    break;
                case NodeType::ImplicitDeclaration:
                    CreateImplicit(child, this);
                    break;
                case NodeType::ExplicitDeclaration:
                    CreateExplict(child, this);
                    break;
                case NodeType::OperatorOverload:
                    CreateOperatorOverload(child, this);
                    break;
                default:
                    PushException(new InvalidGlobalStatementException(child->Token().Index(), parent));
                    break;
            }
        }

        if (CheckDescriber(Describer::Static))
            return;

        TryDeclareExplicitString(this);
        TryDeclareDefaultConstructor(this);
    }

    void ClassSource::BindLocal()
    {
        for (const auto& characteristic : characteristics)
            characteristic.second->BindLocal();

        for (const auto function: functions)
            function.second->BindLocal();

        for (const auto constructor: constructors)
            constructor.second->BindLocal();

        for (const auto cast: implicitCasts)
            cast.second->BindLocal();

        for (const auto cast: explicitCasts)
            cast.second->BindLocal();

        for (const auto overload: overloads)
            overload.second->BindLocal();
    }

    void ClassSource::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Class: " << name << std::endl;
    }

    ClassSource::~ClassSource()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;

        for (const auto function: functions)
            delete function.second;

        for (const auto constructor: constructors)
            delete constructor.second;

        for (const auto indexer: indexers)
            delete indexer.second;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}


