#ifndef CREATION_CONTEXT_H
#define CREATION_CONTEXT_H

#include "../../context_node.h"
#include "../../../Core/Interfaces/DataTypes/i_collection_type.h"

namespace Analysis::Structure::Context
{
    class CreationContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
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
    };

    class CollectionCreationContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;

            const std::string constructorCIL;
            const std::string pushElementCIL;

        public:
            explicit CollectionCreationContext(const Core::Interfaces::ICollectionType* collectionType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            [[nodiscard]] const std::string& ConstructorCIL() const;
            [[nodiscard]] const std::string& PushElementCIL() const;
    };
}

#endif
