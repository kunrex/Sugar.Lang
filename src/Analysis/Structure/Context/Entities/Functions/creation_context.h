#ifndef CREATION_CONTEXT_H
#define CREATION_CONTEXT_H

#include "../../context_node.h"

#include "../../../Core/Interfaces/Creation/i_function.h"

namespace Analysis::Structure::Context
{
    class CreationContext final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* constructor;

        public:
            explicit CreationContext(const Core::Interfaces::IFunction* constructor);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class CollectionCreationContext final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;

            const Core::Interfaces::IDataType* collectionType;

        public:
            explicit CollectionCreationContext(const Core::Interfaces::IDataType* collectionType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class ConstructorCallContext final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* constructor;

        public:
            explicit ConstructorCallContext(const Core::Interfaces::IFunction* constructor);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
