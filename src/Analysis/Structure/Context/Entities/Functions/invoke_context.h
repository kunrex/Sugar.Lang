#ifndef INVOKE_H
#define INVOKE_H

#include "../../context_node.h"
#include "../../../Core/DataTypes/generic_type.h"

namespace Analysis::Structure::Context
{
    class InvokeContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;
            const Core::GenericType* delegateType;

        public:
            InvokeContext(const Core::Interfaces::IDataType* creationType, const Core::GenericType* delegateType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
