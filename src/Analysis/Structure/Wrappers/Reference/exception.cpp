#include "exception.h"

#include "./string.h"

#include "../Value/boolean.h"

#include "../../Global/Properties/property.h"
#include "../../Global/Functions/constructor.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_exception = "[System.Runtime]System.Exception";

namespace Analysis::Structure::Wrappers
{
    Exception::Exception() : ImplicitClass(cil_exception, Describer::Public), SingletonService(), message(nullptr), constructor(nullptr)
    { }

    Exception Exception::instance;

    const Exception* Exception::Instance() { return &instance; }

    void Exception::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    TypeKind Exception::Type() const { return TypeKind::Exception; }

    void Exception::BindGlobal()
    {
        message = new BuiltInProperty("Message", Describer::Public, String::Instance(), true, "callvirt instance string [System.Runtime]System.Exception::get_Message()", false, "");

        const auto constructor = new BuiltInConstructor(this, "instance void [System.Runtime]System.Exception::.ctor(string)");
        constructor->PushParameterType(String::Instance());
        this->constructor = constructor;

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

    const ICharacteristic* Exception::FindCharacteristic(const string& name) const
    {
        if (name == message->Name())
            return message;

        return nullptr;
    }

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

    const IOperatorOverload* Exception::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Exception::~Exception()
    {
        delete message;

        delete constructor;

        for (const auto overload : overloads)
            delete overload.second;
    }
}
