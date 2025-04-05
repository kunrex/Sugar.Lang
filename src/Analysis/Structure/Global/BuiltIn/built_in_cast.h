#ifndef BUILT_IN_CAST_H
#define BUILT_IN_CAST_H

#include "../../Core/built_in_function.h"
#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInCast final : public Creation::CastDefinition, public Core::Interfaces::BuiltInFunction, public virtual Core::Interfaces::IBuiltInCast
    {
        private:
            const Core::Interfaces::CastFunction castDelegate;

        public:
            BuiltInCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::CastFunction castDelegate);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const Compilation::CompilationResult& argument) const override;
    };
}

#endif
