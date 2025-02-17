#ifndef PRINT_H
#define PRINT_H

#include "../../context_node.h"
#include "../../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class Print : public ContextNode, public Services::Collection<ContextNode>
    {
        protected:
            const bool ln;
            const ContextNode* operand;

        public:
            explicit Print(bool ln);
            Print(const ContextNode* operand, bool ln);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const ContextNode* Operand() const;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };

    class PrintChar final : public Print
    {
        public:
            explicit PrintChar(bool ln);
            PrintChar(const ContextNode* operand, bool ln);

        [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintBool final : public Print
    {
        public:
            explicit PrintBool(bool ln);
            PrintBool(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintShort final : public Print
    {
        public:
            explicit PrintShort(bool ln);
            PrintShort(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintInt final : public Print
    {
        public:
            explicit PrintInt(bool ln);
            PrintInt(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintLong final : public Print
    {
        public:
            explicit PrintLong(bool ln);
            PrintLong(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintFloat final : public Print
    {
        public:
            explicit PrintFloat(bool ln);
            PrintFloat(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintDouble final : public Print
    {
        public:
            explicit PrintDouble(bool ln);
            PrintDouble(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintString final : public Print
    {
        public:
            explicit PrintString(bool ln);
            PrintString(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };

    class PrintObject final : public Print
    {
        public:
            explicit PrintObject(bool ln);
            PrintObject(const ContextNode* operand, bool ln);

            [[nodiscard]] std::string InstructionGet() const override;
    };
}

#endif
