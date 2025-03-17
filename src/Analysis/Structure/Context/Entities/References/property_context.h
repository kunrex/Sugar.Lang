#ifndef PROPERTY_CONTEXT_H
#define PROPERTY_CONTEXT_H

#include "../../context_node.h"
#include "../../../Creation/Properties/property_definition.h"

namespace Analysis::Structure::Context
{
    class PropertyContext final : public ContextNode
    {
        private:
            const Creation::PropertyDefinition* property;

        public:
            explicit PropertyContext(const Creation::PropertyDefinition* property);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            [[nodiscard]] const Creation::PropertyDefinition* Property() const;
    };
}

#endif
