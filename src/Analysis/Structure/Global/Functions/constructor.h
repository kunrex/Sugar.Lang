#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped
    {
        public:
            Constructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::NodeCollection<ParseNodes::ParseNode>* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
