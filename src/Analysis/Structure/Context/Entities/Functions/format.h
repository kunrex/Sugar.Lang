#ifndef FORMAT_H
#define FORMAT_H

#include "../../context_node.h"
#include "../../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class Format final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;

        public:
            Format();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
