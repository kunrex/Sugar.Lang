#include "exception.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/BuiltIn/built_in_constructor.h"

#include "./string.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_exception = "[System.Runtime]System.Exception";

namespace Analysis::Structure::Wrappers
{
    Exception::Exception() : BuiltInClass(cil_exception, Describer::Public), SingletonService(), constructor(nullptr)
    { }

    TypeKind Exception::Type() const { return TypeKind::Exception; }

    void Exception::InitializeMembers()
    {
        constructor = new BuiltInConstructor(this, "call instance void class [System.Runtime]System.Exception::.ctor(string)");
        constructor->PushParameterType(&String::Instance());
    }

    const ICharacteristic* Exception::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Exception::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Exception::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        if (ArgumentHash(constructor) == ArgumentHash(argumentList))
            return constructor;

        return nullptr;
    }

    const IIndexerDefinition* Exception::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Exception::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Exception::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Exception::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Exception::~Exception()
    {
        delete constructor;
    }
}
