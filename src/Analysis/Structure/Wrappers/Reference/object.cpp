#include "object.h"

using namespace Analysis::Structure::Enums;

constexpr std::string cil_object = "[System.Runtime]System.Object";

namespace Analysis::Structure::Wrappers
{
    Object::Object() : Class(cil_object, Describer::Public), SingletonService()
    { }

    void Object::InitialiseMembers()
    { }
}