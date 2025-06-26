#include "cast_overload.h"

#include "../../Core/DataTypes/data_type.h"
#include "../../Compilation/compilation_result.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Services;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    CastOverload::CastOverload(const IFunction* const definition) : definition(definition)
    { }

    MemberType CastOverload::MemberType() const { return MemberType::CastOverload; }

    Describer CastOverload::Describer() const { return definition->Describer(); }

    bool CastOverload::ValidateDescriber(const Enums::Describer allowed) const { return definition->ValidateDescriber(allowed); }

    bool CastOverload::MatchDescriber(const Enums::Describer expected) const { return definition->MatchDescriber(expected); }
    bool CastOverload::CheckDescriber(const Enums::Describer describer) const { return definition->CheckDescriber(describer); }

    const IDataType* CastOverload::CreationType() const { return definition->CreationType(); }

    const std::string& CastOverload::FullName() const { return definition->FullName(); }

    unsigned long CastOverload::ParameterCount() const { return definition->ParameterCount(); }
    const IDataType* CastOverload::ParameterAt(const unsigned long index) const { return definition->ParameterAt(index); }

    GeneratedCast::GeneratedCast(const IDataType* const creationType, const std::string& instruction) : Function(Describer::PublicStatic, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType GeneratedCast::MemberType() const { return MemberType::GeneratedCast; }

    BuiltInCast::BuiltInCast(const IDataType* const creationType, const std::string& instruction, const CastFunction castDelegate) : GeneratedCast(creationType, instruction), castDelegate(castDelegate)
    { }

    CompilationResult BuiltInCast::StaticCompile(const CompilationResult& argument) const { return castDelegate(argument); }
}
