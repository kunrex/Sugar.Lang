#include "enum.h"

#include <format>

#include "data_type_extensions.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Binding/binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const string& name, const Enums::Describer describer, const IParseNode* skeleton) : DataType(name, describer | Describer::Static), skeleton(skeleton), fullName(), explicitCasts()
    { }

    MemberType Enum::MemberType() const { return MemberType::Enum; }

    int Enum::SlotCount() const { return 1; }

    TypeKind Enum::Type() const { return TypeKind::Custom; }

    const string& Enum::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void Enum::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const ICharacteristic* Enum::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    void Enum::PushFunction(IFunctionDefinition* const function)
    { }

    const IFunctionDefinition* Enum::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr;}

    void Enum::PushConstructor(IFunction* constructor)
    { }

    const IFunction* Enum::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushIndexer(IIndexerDefinition* const indexer)
    { }

    const IIndexerDefinition* Enum::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushImplicitCast(IFunction* const cast)
    { }

    const IFunction* Enum::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return nullptr;
    }

    void Enum::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* Enum::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? explicitCasts.at(hash) : nullptr;
    }

    void Enum::PushOverload(IOperatorOverload* const overload)
    { }

    const IOperatorOverload* Enum::FindOverload(const SyntaxKind base) const
    {
        return nullptr;
    }

    void Enum::BindGlobal()
    {
        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
        {
            switch (const auto child = skeleton->GetChild(i); child->NodeType())
            {
                case ParseNodes::Enums::NodeType::Expression:
                    BindEnumConstant(child, this);
                    break;
                default:
                    PushException(new Exceptions::InvalidGlobalStatementException(child->Token().Index(), parent));
                    break;
            }
        }
    }

    void Enum::BindLocal()
    {
        for (const auto& characteristic : characteristics)
            characteristic.second->BindLocal();

        for (const auto& cast: explicitCasts)
            cast.second->BindLocal();
    }

    void Enum::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Enum: " << name << std::endl;
    }

    Enum::~Enum()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;

        for (const auto& cast: explicitCasts)
            delete cast.second;
    }
}
