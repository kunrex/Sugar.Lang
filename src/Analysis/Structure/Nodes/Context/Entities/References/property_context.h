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

            const std::string getInstruction;
            const std::string setInstruction;

        public:
            explicit PropertyContext(const Creation::PropertyDefinition* property);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
