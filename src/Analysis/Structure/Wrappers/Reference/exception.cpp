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

const string cil_exception = "[System.Runtime]System.Exception";

namespace Analysis::Structure::Wrappers
{
    Exception::Exception() : BuiltInClass(cil_exception, Describer::Public), SingletonService(), constructor(nullptr)
    { }

    const Exception& Exception::Instance()
    {
        static const Exception instance;
        return instance;
    }

    TypeKind Exception::Type() const { return TypeKind::Exception; }

    void Exception::BindGlobal()
    {
        constructor = new BuiltInConstructor(this, "newobj instance void class [System.Runtime]System.Exception::.ctor(string)");
        constructor->PushParameterType(String::Instance());
    }

    const ICharacteristic* Exception::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Exception::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IConstructor* Exception::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != String::Instance())
            return nullptr;

        return constructor;
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
