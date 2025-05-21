#include "value_type.h"

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
using namespace Analysis::Structure::Core::Interfaces;

constexpr int word_size = 8;

namespace Analysis::Structure::DataTypes
{
    ValueType::ValueType(const string& name, const Enums::Describer describer) : DataType(name, describer)
    {
        slotCount = -1;
    }

    MemberType ValueType::MemberType() const { return MemberType::ValueType; }

    int ValueType::SlotCount() const
    {
        if (slotCount < 0)
        {
            int totalSize = 0, maxSize = 0;

            for (const auto& characteristic : characteristics)
            {
                const auto size = characteristic.second->CreationType()->SlotCount();
                const auto actual_size = size + (word_size - 1) & ~(word_size - 1);

                totalSize += actual_size;
                if (actual_size > maxSize)
                    maxSize = actual_size;
            }

            slotCount = std::ceil(totalSize + (maxSize - 1) & ~(maxSize - 1) / word_size);
        }

        return slotCount;
    }

    const ICharacteristic* ValueType::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    ValueType::~ValueType()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;
    }

    BuiltInValueType::BuiltInValueType(const std::string& name, const Enums::Describer describer) : ValueType(name, describer)
    { }

    const string& BuiltInValueType::FullName() const { return name; }

    void BuiltInValueType::BindLocal()
    { }

    StructSource::StructSource(const string& name, const Enums::Describer describer, const IParseNode* const skeleton) : ValueType(name, describer), skeleton(skeleton), fullName()
    { }

    TypeKind StructSource::Type() const { return TypeKind::Custom; }

    const string& StructSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void StructSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    void StructSource::PushFunction(IFunctionDefinition* const function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const IFunctionDefinition* StructSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? functions.at(hash) : nullptr;
    }

    void StructSource::PushConstructor(IFunction* const constructor)
    {
        constructors[ArgumentHash(constructor) >> 1 | constructor->CheckDescriber(Describer::Static)] = constructor;
    }

    const IFunction* StructSource::FindConstructor(const bool isStatic, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList) >> 1 | isStatic;
        return constructors.contains(hash) ? constructors.at(hash) : nullptr;
    }

    void StructSource::PushIndexer(IIndexerDefinition* const indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IIndexerDefinition* StructSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? indexers.at(hash) : nullptr;
    }

    void StructSource::PushImplicitCast(IFunction* const cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* StructSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? implicitCasts.at(hash) : nullptr;
    }

    void StructSource::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* StructSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? explicitCasts.at(hash) : nullptr;
    }

    void StructSource::PushOverload(IOperatorOverload* const overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const IOperatorOverload* StructSource::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    void StructSource::BindGlobal()
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
        TryDeclareDefaultConstructor(this);
    }

    void StructSource::BindLocal()
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

    void StructSource::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Struct: " << name << std::endl;
    }

    StructSource::~StructSource()
    {
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

        for (const auto& overload: overloads)
            delete overload.second;
    }
}
