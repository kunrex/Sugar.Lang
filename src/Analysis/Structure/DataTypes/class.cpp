#include "class.h"

#include <format>

#include "data_type_extensions.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Binding/binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"
#include "../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

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
        characteristics.push_back(characteristic);
    }

    const ICharacteristic* ClassSource::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    void ClassSource::PushFunction(IFunctionDefinition* const function)
    {
        functions.emplace_back(std::hash<string>()(function->Name()) ^ ArgumentHash(function), function);
    }

    const IFunctionDefinition* ClassSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function : functions)
            if (std::get<0>(function) == hash)
                return std::get<1>(function);

        return nullptr;
    }

    void ClassSource::PushConstructor(IConstructor* const constructor)
    {
        if (constructor->CheckDescriber(Describer::Static))
            constructors.insert(constructors.begin(), { ArgumentHash(constructor), constructor });
        else
            constructors.emplace_back(ArgumentHash(constructor), constructor);
    }

    const IConstructor* ClassSource::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash= ArgumentHash(argumentList);
        for (int i = StaticConstructor() != nullptr; i < constructors.size(); i++)
        {
            if (const auto current = constructors[i]; std::get<0>(current) == hash)
                return std::get<1>(current);
        }

        return nullptr;
    }

    IConstructor* ClassSource::StaticConstructor() const
    {
        if (constructors.empty())
            return nullptr;

        const auto constructor = std::get<1>(constructors[0]);
        return constructor->CheckDescriber(Describer::Static) ? constructor : nullptr;
    }

    IConstructor* ClassSource::InstanceConstructor() const
    {
        for (int i = StaticConstructor() != nullptr; i < constructors.size(); i++)
        {
            if (const auto current = std::get<1>(constructors[i]); !current->ParameterCount())
                return current;
        }

        return nullptr;
    }

    void ClassSource::PushIndexer(IIndexerDefinition* const indexer)
    {
        indexers.emplace_back(ArgumentHash(indexer), indexer);
    }

    const IIndexerDefinition* ClassSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);

        for (const auto indexer : indexers)
            if (std::get<0>(indexer) == hash)
                return std::get<1>(indexer);

        return nullptr;
    }

    void ClassSource::PushImplicitCast(IFunction* const cast)
    {
        implicitCasts.emplace_back(ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)})), cast);
    }

    const IFunction* ClassSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));

        for (const auto cast : implicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    void ClassSource::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts.emplace_back(ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)})), cast);
    }

    const IFunction* ClassSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));

        for (const auto cast : explicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    void ClassSource::PushOverload(IOperatorOverload* const overload)
    {
        overloads.emplace_back(overload->Operator(), overload);
    }

    const IOperatorOverload* ClassSource::FindOverload(const SyntaxKind base) const
    {
        for (const auto cast : overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
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

        TryDeclareStaticConstructor(this);

        if (CheckDescriber(Describer::Static))
            return;

        TryDeclareExplicitString(this);

        TryDeclareInstanceConstructor(this);
    }

    void ClassSource::BindLocal()
    {
        for (const auto characteristic : characteristics)
            characteristic->BindLocal();

        for (const auto function: functions)
            std::get<1>(function)->BindLocal();

        for (const auto constructor: constructors)
            std::get<1>(constructor)->BindLocal();

        for (const auto cast: implicitCasts)
            std::get<1>(cast)->BindLocal();

        for (const auto cast: explicitCasts)
            std::get<1>(cast)->BindLocal();

        for (const auto overload: overloads)
            std::get<1>(overload)->BindLocal();
    }

    void ClassSource::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine();
        builder.PushLine(std::format(".class {} {} sequential ansi {} extends [System.Runtime]System.Object", AccessModifierString(this), StaticModifierString(this), name));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        for (const auto characteristic : characteristics)
            characteristic->Transpile(builder);

        for (const auto function: functions)
            std::get<1>(function)->Transpile(builder);

        for (const auto constructor: constructors)
            std::get<1>(constructor)->Transpile(builder);

        for (const auto cast: implicitCasts)
            std::get<1>(cast)->Transpile(builder);

        for (const auto cast: explicitCasts)
            std::get<1>(cast)->Transpile(builder);

        for (const auto overload: overloads)
            std::get<1>(overload)->Transpile(builder);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void ClassSource::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Class: " << name << std::endl;
    }

    ClassSource::~ClassSource()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete std::get<1>(function);

        for (const auto constructor: constructors)
            delete std::get<1>(constructor);

        for (const auto indexer: indexers)
            delete std::get<1>(indexer);

        for (const auto cast: implicitCasts)
            delete std::get<1>(cast);

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
