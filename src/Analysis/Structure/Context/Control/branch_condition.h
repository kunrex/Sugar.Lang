#ifndef BRANCH_CONDITION_H
#define BRANCH_CONDITION_H

#include "../context_node.h"
#include "../../Local/Scopes/block.h"

namespace Analysis::Structure::Context
{
    class BranchTrue final : public ContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit BranchTrue(const std::string& name);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };

    class BranchFalse final : public ContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit BranchFalse(const std::string& name);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
