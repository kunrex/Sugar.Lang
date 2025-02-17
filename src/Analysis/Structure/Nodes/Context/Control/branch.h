#ifndef BRANCH_H
#define BRANCH_Hv

#include "../context_node.h"
#include "../../Local/Scopes/block.h"

namespace Analysis::Structure::Context
{
    class Branch final : public ContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit Branch(const std::string& name);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
