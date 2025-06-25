#ifndef CAST_OVERLOAD_H
#define CAST_OVERLOAD_H

#include "../../Creation/Functions/cast_definition.h"

#include "../../Core/Scoped/scoped.h"
#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class DefinedCast : public Core::Nameable, public Creation::CastDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            DefinedCast(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class ImplicitCast final : public DefinedCast
    {
        public:
            ImplicitCast(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);
    };

    class ExplicitCast final : public DefinedCast
    {
        public:
            ExplicitCast(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);
    };

    class GeneratedCast : public Creation::CastDefinition, public Core::BuiltInFunction
    {
        public:
            GeneratedCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class BuiltInCast final : public GeneratedCast, public virtual Core::Interfaces::IBuiltInCast
    {
        private:
            const Core::Interfaces::CastFunction castDelegate;

        public:
            BuiltInCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::CastFunction castDelegate);

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const Compilation::CompilationResult& argument) const override;
    };
}

#endif
