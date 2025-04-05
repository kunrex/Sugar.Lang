#ifndef LOCAL_VARIABLE_CONTEXT_H
#define LOCAL_VARIABLE_CONTEXT_H

#include "../../context_node.h"

#include "../../../Core/Interfaces/Creation/i_variable.h"

namespace Analysis::Structure::Context
{
    class LocalVariableContext : public ContextNode
    {
        protected:
            const int index;
            const Core::Interfaces::IVariable* variable;

        public:
            LocalVariableContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
