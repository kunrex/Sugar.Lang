#ifndef STRING_CONSTANT_H
#define STRING_CONSTANT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class StringConstant final : public ContextNode
    {
        private:
            const std::string value;

        public:
            explicit StringConstant(std::string value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
