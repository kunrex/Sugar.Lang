#ifndef PRINTLN_H
#define PRINTLN_H

#include "../../context_node.h"
#include "../../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class Println final : public ContextNode, public Services::Collection<ContextNode>
    {
        public:
            Println();

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
