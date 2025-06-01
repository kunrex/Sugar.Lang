#include "void.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    Void::Void() : BuiltInClass("void", Enums::Describer::Public)
    { }

    Void Void::instance;

    const Void* Void::Instance() { return &instance; }

    void Void::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Void::SlotCount() const { return 0; }

    TypeKind Void::Type() const { return TypeKind::Void; }

    void Void::BindGlobal()
    { }

    const ICharacteristic* Void::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Void::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IConstructor* Void::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Void::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Void::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Void::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Void::FindOverload(const SyntaxKind base) const
    { return nullptr; }
}
