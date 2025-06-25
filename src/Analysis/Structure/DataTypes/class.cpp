#include "class.h"

#include <format>

#include "data_type_extensions.h"

#include "../Wrappers/Value/boolean.h"
#include "../Wrappers/Value/integer.h"
#include "../Wrappers/Reference/object.h"
#include "../Wrappers/Reference/string.h"

#include "../Global/Functions/void_function.h"
#include "../Global/Functions/cast_overload.h"
#include "../Global/Functions/method_function.h"
#include "../Global/Functions/operator_overload.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Transpiling/cil_transpiler.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    Class::Class(const std::string& name, const Enums::Describer describer) : DataType(name, describer)
    { }

    MemberType Class::MemberType() const { return MemberType::Class; }

    int Class::SlotCount() const { return 1; }

    IFunctionDefinition* Class::GetHash()
    {
        return new BuiltInMethod(std::string(hashCodeFunction), Describer::Public, Integer::Instance(), "callvirt instance int32 [System.Runtime]System.Object::GetHashCode()");
    }

    IFunction* Class::ImplicitObject() const
    {
        const auto cast = new GeneratedCast(Object::Instance(), "nop");
        cast->PushParameterType(this);
        return cast;
    }

    BuiltInClass::BuiltInClass(const std::string& name, const Enums::Describer describer) : Class(name, describer)
    { }

    const std::string& BuiltInClass::FullName() const { return name; }

    void BuiltInClass::BindLocal()
    { }

    ImplicitClass::ImplicitClass(const std::string& name, const Enums::Describer describer) : BuiltInClass(name, describer), getHash(nullptr), explicitString(nullptr), implicitObject(nullptr)
    { }

    void ImplicitClass::BindGlobal()
    {
        const auto explicitString = new GeneratedCast(String::Instance(), "callvirt instance string [System.Runtime]System.Object::ToString()");
        explicitString->PushParameterType(this);
        this->explicitString = explicitString;

        getHash = GetHash();
        implicitObject = ImplicitObject();
    }

    const IFunctionDefinition* ImplicitClass::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name == getHash->Name() && argumentList.empty())
            return getHash;

        return nullptr;
    }

    const IFunction* ImplicitClass::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == String::Instance() && fromType == this)
            return explicitString;

        return nullptr;
    }

    const IFunction* ImplicitClass::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == Object::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    ImplicitClass::~ImplicitClass()
    {
        delete getHash;

        delete explicitString;

        delete implicitObject;
    }


    ClassSource::ClassSource(const std::string& name, const Enums::Describer describer, const IParseNode* skeleton) : Class(name, describer), skeleton(skeleton), fullName()
    { }

    TypeKind ClassSource::Type() const { return TypeKind::Custom; }

    const std::string& ClassSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void ClassSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics.push_back(characteristic);
    }

    const ICharacteristic* ClassSource::FindCharacteristic(const std::string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    void ClassSource::PushFunction(IFunctionDefinition* const function)
    {
        functions.emplace_back(std::hash<std::string>()(function->Name()) ^ ArgumentHash(function), function);
    }

    const IFunctionDefinition* ClassSource::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<std::string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function : functions)
            if (function.first == hash)
                return function.second;

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
            if (const auto current = constructors[i]; current.first == hash)
                return current.second;
        }

        return nullptr;
    }

    IConstructor* ClassSource::StaticConstructor() const
    {
        if (constructors.empty())
            return nullptr;

        const auto constructor = constructors[0].second;
        return constructor->CheckDescriber(Describer::Static) ? constructor : nullptr;
    }

    IConstructor* ClassSource::InstanceConstructor() const
    {
        for (int i = StaticConstructor() != nullptr; i < constructors.size(); i++)
        {
            if (const auto current = constructors[i].second; !current->ParameterCount())
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
            if (indexer.first == hash)
                return indexer.second;

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
            if (cast.first == hash)
                return cast.second;

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
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    void ClassSource::PushOverload(IOperatorOverload* const overload)
    {
        overloads.emplace_back(overload->Operator(), overload);
    }

    const IOperatorOverload* ClassSource::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload : overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    void ClassSource::BindGlobal()
    {
        PushFunction(GetHash());

        const auto implicitObject = new GeneratedCast(Object::Instance(), "nop");
        implicitObject->PushParameterType(this);
        PushImplicitCast(implicitObject);

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
                case NodeType::IndexerDeclaration:
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
                    ExceptionManager::PushException(InvalidGlobalStatementException(child->Token().Index(), parent));
                    break;
            }
        }

        TryDeclareStaticConstructor(this);

        if (CheckDescriber(Describer::Static))
            return;

        TryDeclareInstanceConstructor(this);

        if (FindExplicitCast(String::Instance(), this) == nullptr)
        {
            const auto cast = new GeneratedCast(String::Instance(), std::format("callvirt instance string class {}::ToString()", FullName()));
            cast->PushParameterType(this);
            PushExplicitCast(cast);
        }

        auto flag = false;
        if (FindOverload(SyntaxKind::Equals) == nullptr)
        {
            const auto equals = new ImplicitOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq");
            equals->PushParameterType(this);
            equals->PushParameterType(this);
            PushOverload(equals);

            flag = !flag;
        }

        if (FindOverload(SyntaxKind::NotEquals) == nullptr)
        {
            const auto notEquals = new ImplicitOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq");
            notEquals->PushParameterType(this);
            notEquals->PushParameterType(this);
            PushOverload(notEquals);

            flag = !flag;
        }

        if (flag)
            ExceptionManager::PushException(LogException(std::format("Type: {} must define overloads for both == and !=", FullName()), skeleton->Token().Index(), parent));

        if (FindOverload(SyntaxKind::GreaterThan) == nullptr ^ FindOverload(SyntaxKind::LesserThan) == nullptr)
            ExceptionManager::PushException(LogException(std::format("Type: {} must define overloads for both < and >", FullName()), skeleton->Token().Index(), parent));

        if (FindOverload(SyntaxKind::GreaterThanEquals) == nullptr ^ FindOverload(SyntaxKind::LesserThanEquals) == nullptr)
            ExceptionManager::PushException(LogException(std::format("Type: {} must define overloads for both <= and >=", FullName()), skeleton->Token().Index(), parent));
    }

    void ClassSource::BindLocal()
    {
        for (const auto characteristic : characteristics)
            characteristic->BindLocal();

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

    void ClassSource::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine(std::format(".class {} {} sequential ansi {} extends [System.Runtime]System.Object", AccessModifierString(this), StaticModifierString(this), fullName));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        for (const auto characteristic : characteristics)
            characteristic->Transpile(builder);

        for (const auto function: functions)
            function.second->Transpile(builder);

        for (const auto constructor: constructors)
            constructor.second->Transpile(builder);

        for (const auto cast: implicitCasts)
            cast.second->Transpile(builder);

        for (const auto cast: explicitCasts)
            cast.second->Transpile(builder);

        for (const auto overload: overloads)
            overload.second->Transpile(builder);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);

        builder.WriteToFile();
    }

    void ClassSource::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Class: " << name << std::endl;
    }

    ClassSource::~ClassSource()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic;

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
