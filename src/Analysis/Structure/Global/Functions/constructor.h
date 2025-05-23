#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            Constructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;
    };
}

#endif
