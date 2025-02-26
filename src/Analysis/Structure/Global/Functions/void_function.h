#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class VoidFunction final : public Creation::VoidDefinition, public Core::Scoped
    {
        public:
            VoidFunction(const std::string& name, Enums::Describer describer, const ParseNodes::NodeCollection<ParseNodes::ParseNode>* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
