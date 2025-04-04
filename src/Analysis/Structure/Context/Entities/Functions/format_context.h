#ifndef FORMAT_CONTEXT_H
#define FORMAT_CONTEXT_H

#include "../../binary_context_node.h"
#include "../../context_node.h"
#include "../../unary_context_node.h"
#include "../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class FormatContext final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;

        public:
            FormatContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };

    class FormatSingleContext final : public UnaryContextNode
    {
        private:
            const int slotCount;

        public:
            explicit FormatSingleContext(const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };

    class FormatDoubleContext final : public BinaryContextNode
    {
        private:
            mutable int slotCount;

        public:
            explicit FormatDoubleContext(const IContextNode* arg1, const IContextNode* arg2);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
