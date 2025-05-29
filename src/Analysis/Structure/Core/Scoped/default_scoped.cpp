#include "default_scoped.h"

#include "../../Wrappers/Reference/void.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

const string default_name = "default";

namespace Analysis::Structure::Core
{
    DefaultScoped::DefaultScoped() : scope(new Local::Scope(ScopeType::Scope, default_name, this))
    { }

    Scope* DefaultScoped::Scope() const { return scope; }

    unsigned long DefaultScoped::ParameterCount() const { return 0; }
    const IDataType* DefaultScoped::ParameterAt(unsigned long index) const { return nullptr; }

    unsigned long DefaultScoped::VariableCount() const { return 0; }
    const LocalVariable* DefaultScoped::VariableAt(unsigned long i) const { return nullptr; }

    std::optional<unsigned long> DefaultScoped::GetParameterIndex(const std::string& name) const {  return std::nullopt; }

    void DefaultScoped::AddParameter(const LocalVariable* const parameter)
    { }

    void DefaultScoped::AddLocalVariable(const LocalVariable* const variable)
    { }

    DefaultScoped::~DefaultScoped()
    {
        delete scope;
    }
}
