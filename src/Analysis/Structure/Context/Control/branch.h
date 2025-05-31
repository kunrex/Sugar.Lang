#ifndef BRANCH_H
#define BRANCH_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class Branch final : public ContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit Branch(const std::string& name);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
