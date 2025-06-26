#include "array.h"

#include <map>
#include <format>

#include "../Value/integer.h"
#include "../Value/boolean.h"
#include "../Reference/object.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/operator_overload.h"

#include "../../Global/Properties/indexer.h"
#include "../../Global/Properties/property.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    Array::Array(const IDataType* const arrayType) : ImplicitClass(std::format("{} {}[]", arrayType->MemberType() == MemberType::Class ? "class" : "valuetype", arrayType->FullName()), Describer::Public), SingletonService(), genericSignature(), arrayType(arrayType), length(nullptr), constructor(nullptr), indexer(nullptr)
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

        array->BindGlobal();

        map[hash] = array;
        return array;
    }

    TypeKind Array::Type() const { return TypeKind::Array; }

    const std::string& Array::FullName() const { return genericSignature; }

    const IDataType* Array::GenericType() const { return arrayType; }

    void Array::BindGlobal()
    {
        length = new BuiltInProperty("Length", Describer::Public, Integer::Instance(), true, "ldlen", false, "");

        const auto constructor = new BuiltInConstructor(this, std::format("newarr {}", arrayType->FullName()));
        constructor->PushParameterType(Integer::Instance());
        this->constructor = constructor;

        if (arrayType->MemberType() == MemberType::Class)
        {
            const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.ref", true, "stelem.ref");
            indexer->PushParameterType(Integer::Instance());
            this->indexer = indexer;
        }
        else
        {
            switch (arrayType->Type())
            {
                case TypeKind::Short:
                case TypeKind::Character:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.i2", true, "stelem.i2");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                case TypeKind::Int:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.i4", true, "stelem.i4");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                case TypeKind::Long:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.i8", true, "stelem.i8");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                case TypeKind::Boolean:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.i1", true, "stelem.i1");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                case TypeKind::Float:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.r4", true, "stelem.r4");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                case TypeKind::Double:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem.r8", true, "stelem.r8");
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
                default:
                    {
                        const auto indexer = new BuiltInIndexer(arrayType, true, "ldelem " + arrayType->FullName(), true, "stelem " + arrayType->FullName());
                        indexer->PushParameterType(Integer::Instance());
                        this->indexer = indexer;
                    }
                    break;
            }

        }

        const auto equals = new GeneratedOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new GeneratedOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };

        ImplicitClass::BindGlobal();
    }

    const ICharacteristic* Array::FindCharacteristic(const std::string& name) const
    {
        if (name == length->Name())
            return length;

        return nullptr;
    }

    const IConstructor* Array::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != Integer::Instance())
            return nullptr;

        return constructor;
    }

    const IIndexerDefinition* Array::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != Integer::Instance())
            return nullptr;

        return indexer;
    }

    const IOperatorOverload* Array::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Array::~Array()
    {
        delete length;

        delete constructor;

        delete indexer;

        for (const auto overload : overloads)
            delete overload.second;
    }
}
