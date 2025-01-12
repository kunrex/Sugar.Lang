#ifndef INPUT_H
#define INPUT_H

#include "../../context_node.h"
#include "../../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class Input final : public ContextNode
    {
        public:
            Input();

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
