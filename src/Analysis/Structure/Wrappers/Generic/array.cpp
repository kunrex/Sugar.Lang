#include "array.h"

#include <map>

#include <format>

#include "../../Global/BuiltIn/built_in_property.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/BuiltIn/built_in_constructor.h"
#include "../../Global/BuiltIn/built_in_indexer.h"

#include "../Value/integer.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    Array::Array(const IDataType* const arrayType) : BuiltInClass(std::format("{} {}[]", arrayType->MemberType() == MemberType::Class ? "class" : "valuetype", arrayType->FullName()), Describer::Public), SingletonService(), genericSignature(), arrayType(arrayType), length(nullptr), constructor(nullptr), indexer(nullptr)
    { }

    const Array* Array::Instance(const IDataType* const dataType)
    {
        static std::map<unsigned long, const Array*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto array = new Array(dataType);
        array->genericSignature = std::format("{} {}[]", dataType->MemberType() == MemberType::Class ? "class" : "valuetype", dataType->FullName());

        array->InitializeMembers();

        map[hash] = array;
        return array;
    }

    TypeKind Array::Type() const { return TypeKind::Array; }

    const std::string& Array::FullName() const { return genericSignature; }

    const IDataType* Array::GenericType() const { return arrayType; }

    void Array::InitializeMembers()
    {
        length = new BuiltInProperty(Describer::Public, "Length", &Integer::Instance(), true, "ldlen", false, "");

        constructor = new BuiltInConstructor(this, std::format("newarr {}", arrayType->FullName()));
        constructor->PushParameterType(&Integer::Instance());

        if (arrayType->MemberType() == MemberType::Class)
        {
            indexer = new BuiltInIndexer(arrayType, true, "ldelem.ref", true, "stelem.ref");
            indexer->PushParameterType(&Integer::Instance());
        }
        else
        {
            indexer = new BuiltInIndexer(arrayType, true, "ldelem", true, "stelem");
            indexer->PushParameterType(&Integer::Instance());
        }
    }

    const ICharacteristic* Array::FindCharacteristic(const std::string& name) const
    {
        return length->Name() == name ? length : nullptr;
    }

    const IFunction* Array::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(constructor) == ArgumentHash(argumentList) ? constructor : nullptr;
    }

    const IFunctionDefinition* Array::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Array::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(indexer) == ArgumentHash(argumentList) ? indexer : nullptr;
    }

    const IFunction* Array::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Array::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Array::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Array::~Array()
    {
        delete length;

        delete constructor;

        delete indexer;
    }
}
