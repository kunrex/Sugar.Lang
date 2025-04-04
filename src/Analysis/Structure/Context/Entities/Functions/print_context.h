#ifndef PRINT_H
#define PRINT_H

#include "../../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class PrintContext : public UnaryContextNode
    {
        protected:
            const bool ln;
            const int slotCount;

        public:
            explicit PrintContext(bool ln);
            PrintContext(const IContextNode* operand, bool ln);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintCharContext final : public PrintContext
    {
        public:
            explicit PrintCharContext(bool ln);
            PrintCharContext(const IContextNode* operand, bool ln);

        [[nodiscard]] std::string CILData() const override;
    };

    class PrintBoolContext final : public PrintContext
    {
        public:
            explicit PrintBoolContext(bool ln);
            PrintBoolContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintShortContext final : public PrintContext
    {
        public:
            explicit PrintShortContext(bool ln);
            PrintShortContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintIntContext final : public PrintContext
    {
        public:
            explicit PrintIntContext(bool ln);
            PrintIntContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintLongContext final : public PrintContext
    {
        public:
            explicit PrintLongContext(bool ln);
            PrintLongContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintFloatContext final : public PrintContext
    {
        public:
            explicit PrintFloatContext(bool ln);
            PrintFloatContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintDoubleContext final : public PrintContext
    {
        public:
            explicit PrintDoubleContext(bool ln);
            PrintDoubleContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintStringContext final : public PrintContext
    {
        public:
            explicit PrintStringContext(bool ln);
            PrintStringContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };

    class PrintObjectContext final : public PrintContext
    {
        public:
            explicit PrintObjectContext(bool ln);
            PrintObjectContext(const IContextNode* operand, bool ln);

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
