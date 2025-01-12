#ifndef PRINT_H
#define PRINT_H

#include "../../context_node.h"
#include "../../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class Print final : public ContextNode, public Services::Collection<ContextNode>
    {
        public:
            Print();

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
