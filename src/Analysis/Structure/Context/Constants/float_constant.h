#ifndef FLOAT_CONSTANT_H
#define FLOAT_CONSTANT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class FloatConstant final : public ContextNode
    {
        private:
            const float value;

        public:
            explicit FloatConstant(float value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };

    class DoubleConstant final : public ContextNode
    {
        private:
            const double value;

        public:
            explicit DoubleConstant(double value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
