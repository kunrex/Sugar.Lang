#ifndef FUNCREF_H
#define FUNCREF_H

#include "../../unary_context_node.h"

#include "../../../Core/Interfaces/Creation/i_function_definition.h"

namespace Analysis::Structure::Context
{
    class FuncRefContext final : public UnaryContextNode
    {
        private:
            const int slotCount;
            const Core::Interfaces::IFunctionDefinition* function;

        public:
            FuncRefContext(const Core::Interfaces::IDataType* creationType, const IContextNode* object, const Core::Interfaces::IFunctionDefinition* function);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
