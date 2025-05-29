#ifndef EXPLICIT_CAST_H
#define EXPLICIT_CAST_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/cast_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class ExplicitCast final : public Core::Nameable, public Creation::CastDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            ExplicitCast(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };
}

#endif
