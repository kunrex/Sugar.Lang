#ifndef CAST_OVERLOAD_H
#define CAST_OVERLOAD_H

#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Structure::Global
{
    class CastOverload final : public virtual Core::Interfaces::IFunction
    {
        private:
            const IFunction* definition;

        public:
            explicit CastOverload(const IFunction* definition);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] Enums::Describer Describer() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* CreationType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool ValidateDescriber(Enums::Describer allowed) const override;

            [[nodiscard]] bool MatchDescriber(Enums::Describer expected) const override;
            [[nodiscard]] bool CheckDescriber(Enums::Describer describer) const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };

    class GeneratedCast : public Core::Function, public Core::BuiltInFunction
    {
        public:
            GeneratedCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;
    };

    class BuiltInCast final : public GeneratedCast, public virtual Core::Interfaces::IBuiltInCast
    {
        private:
            const Core::Interfaces::CastFunction castDelegate;

        public:
            BuiltInCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::CastFunction castDelegate);

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const Compilation::CompilationResult& argument) const override;
    };
}

#endif
