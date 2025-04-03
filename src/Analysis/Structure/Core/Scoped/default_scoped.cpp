#include "default_scoped.h"

#include "../../Wrappers/Reference/void.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string default_scoped_name = "default_scoped";

namespace Analysis::Structure::Core
{
    DefaultScoped::DefaultScoped(const Enums::Describer describer) : Describable(describer), scope(ScopeType::Scope, default_scoped_name, this)
    { }

    const IParseNode* DefaultScoped::ParseNode() const { return nullptr; }

    Scope* DefaultScoped::Scope() const { return &scope; }

    MemberType DefaultScoped::MemberType() const { return MemberType::Scope; }

    const std::string& DefaultScoped::Name() const { return default_scoped_name; }
    const std::string& DefaultScoped::FullName() const { return default_scoped_name; }

    const IDataType* DefaultScoped::CreationType() const { return &Void::Instance(); }

    unsigned long DefaultScoped::ParameterCount() const { return 0; }
    const IDataType* DefaultScoped::ParameterAt(unsigned long index) const { return nullptr; }

    unsigned long DefaultScoped::VariableCount() const { return 0; }
    const LocalVariable* DefaultScoped::VariableAt(unsigned long i) const { return nullptr; }

    std::optional<unsigned long> DefaultScoped::GetParameterIndex(const std::string& name) const {  return std::nullopt; }

    void DefaultScoped::AddParameter(const LocalVariable* const parameter)
    { }

    void DefaultScoped::AddLocalVariable(const LocalVariable* const variable)
    { }
}
