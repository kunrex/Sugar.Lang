#include "built_in_cast.h"

#include "../../Compilation/compilation_result.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInCast::BuiltInCast(const IDataType* const creationType, const string& instruction, const CastFunction castDelegate) : CastDefinition(Describer::PublicStatic, creationType), BuiltInFunction(), castDelegate(castDelegate)
    {
        fullName = instruction;
    }

    MemberType BuiltInCast::MemberType() const { return MemberType::BuiltInCast; }

    const string& BuiltInCast::FullName() const { return fullName; }

    CompilationResult BuiltInCast::StaticCompile(const CompilationResult& argument) const { return castDelegate(argument); }

    void BuiltInCast::Bind()
    { }
}
