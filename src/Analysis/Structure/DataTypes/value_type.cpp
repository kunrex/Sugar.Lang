#include "value_type.h"

#include <format>

#include "data_type_extensions.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Binding/binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"
#include "../../Creation/Transpiling/cil_transpiler.h"
#include "../Global/Functions/cast_overload.h"
#include "../Global/Functions/method_function.h"
#include "../Wrappers/Reference/string.h"
#include "../Wrappers/Value/integer.h"

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
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

constexpr int word_size = 8;

namespace Analysis::Structure::DataTypes
{
    ValueType::ValueType(const string& name, const Enums::Describer describer) : DataType(name, describer), slotCount(-1)
    { }

    MemberType ValueType::MemberType() const { return MemberType::ValueType; }

    IFunctionDefinition* ValueType::GetHash() const
    {
        return new BuiltInMethod(std::string(hashCodeFunction), Describer::Public, Integer::Instance(), std::format("constrained. {} callvirt instance int32 [System.Runtime]System.Object::GetHashCode()", FullName()));
    }

    BuiltInValueType::BuiltInValueType(const std::string& name, const Enums::Describer describer) : ValueType(name, describer)
    { }

    const string& BuiltInValueType::FullName() const { return name; }

    void BuiltInValueType::BindLocal()
    { }

    ImplicitValueType::ImplicitValueType(const std::string& name, const Enums::Describer describer) : BuiltInValueType(name, describer), getHash(nullptr), explicitString(nullptr)
    { }

    void ImplicitValueType::BindGlobal()
    {
        getHash = GetHash();

        const auto explicitString = new GeneratedCast(String::Instance(), std::format("constrained. valuetype {} call instance string [System.Runtime]System.Object::ToString()", FullName()));
        explicitString->PushParameterType(this);
        this->explicitString = explicitString;
    }

    const IFunctionDefinition* ImplicitValueType::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name == getHash->Name() && argumentList.empty())
            return getHash;

        return nullptr;
    }

    const IFunction* ImplicitValueType::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == String::Instance() && fromType == this)
            return explicitString;

        return nullptr;
    }

    ImplicitValueType::~ImplicitValueType()
    {
        delete getHash;

        delete explicitString;
    }

    StructSource::StructSource(const string& name, const Enums::Describer describer, const IParseNode* const skeleton) : ValueType(name, describer), skeleton(skeleton), fullName()
    { }

    int StructSource::SlotCount() const
    {
        if (slotCount < 0)
        {
            int totalSize = 0, maxSize = 0;

            for (const auto& characteristic : characteristics)
            {
                if (characteristic->CheckDescriber(Describer::Static))
                    continue;

                const auto size = characteristic->CreationType()->SlotCount();
                const auto actual_size = size + (word_size - 1) & ~(word_size - 1);

                totalSize += actual_size;
                if (actual_size > maxSize)
                    maxSize = actual_size;
            }

            slotCount = std::ceil(totalSize + (maxSize - 1) & ~(maxSize - 1) / word_size);
        }

        return slotCount;
    }

    TypeKind StructSource::Type() const { return TypeKind::Custom; }

    const string& StructSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void StructSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics.push_back(characteristic);
    }

    const ICharacteristic* StructSource::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    void StructSource::PushFunction(IFunctionDefinition* const function)
    {
        functions.emplace_back(std::hash<string>()(function->Name()) ^ ArgumentHash(function), function);
    }

    const IFunctionDefinition* StructSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);

        for (const auto function : functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    void StructSource::PushConstructor(IConstructor* const constructor)
    {
        if (constructor->CheckDescriber(Describer::Static))
            constructors.insert(constructors.begin(), { ArgumentHash(constructor), constructor });
        else
            constructors.emplace_back(ArgumentHash(constructor), constructor);
    }

    const IConstructor* StructSource::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash= ArgumentHash(argumentList);
        for (int i = StaticConstructor() != nullptr; i < constructors.size(); i++)
        {
            if (const auto current = constructors[i]; current.first == hash)
                return current.second;
        }

        return nullptr;
    }

    IConstructor* StructSource::StaticConstructor() const
    {
        if (constructors.empty())
            return nullptr;

        const auto constructor = constructors[0].second;
        return constructor->CheckDescriber(Describer::Static) ? constructor : nullptr;
    }

    IConstructor* StructSource::InstanceConstructor() const
    {
        for (int i = StaticConstructor() != nullptr; i < constructors.size(); i++)
        {
            if (const auto current = constructors[i].second; !current->ParameterCount())
                return current;
        }

        return nullptr;
    }

    void StructSource::PushIndexer(IIndexerDefinition* const indexer)
    {
        indexers.emplace_back(ArgumentHash(indexer), indexer);
    }

    const IIndexerDefinition* StructSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);

        for (const auto indexer : indexers)
            if (indexer.first == hash)
                return indexer.second;

        return nullptr;
    }

    void StructSource::PushImplicitCast(IFunction* const cast)
    {
        implicitCasts.emplace_back(ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)})), cast);
    }

    const IFunction* StructSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));

        for (const auto cast : implicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    void StructSource::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts.emplace_back(ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)})), cast);
    }

    const IFunction* StructSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));

        for (const auto cast : explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    void StructSource::PushOverload(IOperatorOverload* const overload)
    {
        overloads.emplace_back(overload->Operator(), overload);
    }

    const IOperatorOverload* StructSource::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload : overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    void StructSource::BindGlobal()
    {
        PushFunction(GetHash());

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
                    PushException(new InvalidGlobalStatementException(child->Token().Index(), parent));
                    break;
            }
        }

        TryDeclareStaticConstructor(this);

        if (CheckDescriber(Describer::Static))
            return;

        TryDeclareInstanceConstructor(this);

        if (FindExplicitCast(String::Instance(), this) == nullptr)
        {
            const auto cast = new GeneratedCast(String::Instance(), std::format("constrained. {} callvirt instance string class [System.Runtime]Object::ToString()", FullName()));
            cast->PushParameterType(this);
            PushExplicitCast(cast);
        }

        if (FindOverload(SyntaxKind::Equals) == nullptr ^ FindOverload(SyntaxKind::NotEquals) == nullptr)
            PushException(new LogException(std::format("Type: {} must define overloads for both == and !=", FullName()), skeleton->Token().Index(), parent));

        if (FindOverload(SyntaxKind::GreaterThan) == nullptr ^ FindOverload(SyntaxKind::LesserThan) == nullptr)
            PushException(new LogException(std::format("Type: {} must define overloads for both < and >", FullName()), skeleton->Token().Index(), parent));

        if (FindOverload(SyntaxKind::GreaterThanEquals) == nullptr ^ FindOverload(SyntaxKind::LesserThanEquals) == nullptr)
            PushException(new LogException(std::format("Type: {} must define overloads for both <= and >=", FullName()), skeleton->Token().Index(), parent));
    }

    void StructSource::BindLocal()
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

    void StructSource::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine(std::format(".class {} {} auto ansi {} extends [System.Runtime]System.TypeValue", AccessModifierString(this), StaticModifierString(this), fullName));

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
    }

    void StructSource::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Struct: " << name << std::endl;
    }

    StructSource::~StructSource()
    {
        for (const auto characteristic : characteristics)
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
