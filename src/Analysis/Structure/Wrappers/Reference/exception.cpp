#include "exception.h"

#include "../../Nodes/Global/BuiltIn/built_in_constructor.h"

#include "./string.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_exception = "[System.Runtime]System.Exception";

namespace Analysis::Structure::Wrappers
{
    Exception::Exception() : Class(cil_exception, Describer::Public), SingletonService()
    { }

    void Exception::InitialiseMembers()
    {
        const auto defaultConstructor = new BuiltInConstructor(&Instance(), "newobj instance void [mscorlib]System.Exception::.ctor(string)");
        defaultConstructor->PushParameterType(&String::Instance());
        PushConstructor(defaultConstructor);
    }
}
