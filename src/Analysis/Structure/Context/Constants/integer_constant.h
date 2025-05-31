#ifndef INTEGER_CONSTANT_H
#define INTEGER_CONSTANT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class ShortConstant final : public ContextNode
    {
        private:
            const short value;

        public:
            explicit ShortConstant(short value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class IntegerConstant final : public ContextNode
    {
        private:
            const int value;

        public:
            explicit IntegerConstant(int value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class LongConstant final : public ContextNode
    {
        private:
            const long value;

        public:
            explicit LongConstant(long value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class CharacterConstant final : public ContextNode
    {
        private:
            const char value;

        public:
            explicit CharacterConstant(char value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class BoolConstant : public ContextNode
    {
        protected:
            const bool value;
            explicit BoolConstant(bool value);

        public:
            [[nodiscard]] uintptr_t Metadata() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class TrueConstant final : public BoolConstant
    {
        public:
            TrueConstant();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };

    class FalseConstant final : public BoolConstant
    {
        public:
            FalseConstant();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
