#ifndef PROPERTY_CONTEXT_H
#define PROPERTY_CONTEXT_H

#include "../../context_node.h"
#include "../../../Creation/Properties/property.h"

namespace Analysis::Structure::Context
{
    class PropertyContext final : public ContextNode
    {
        private:
            const Creation::Property* property;

        public:
            explicit PropertyContext(const Creation::Property* property);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
