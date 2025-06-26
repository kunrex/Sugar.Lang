#ifndef PROPERTY_CONTEXT_H
#define PROPERTY_CONTEXT_H

#include "../../context_node.h"

#include "../../../Global/Properties/property.h"

namespace Analysis::Structure::Context
{
    class PropertyContext final : public ContextNode
    {
        private:
            const bool isPublic;
            const Global::PropertyDefinition* property;

        public:
            PropertyContext(const Global::PropertyDefinition* property, bool isPublic);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
