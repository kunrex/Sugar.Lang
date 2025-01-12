#ifndef LOCAL_VARIABLE_CONTEXT_H
#define LOCAL_VARIABLE_CONTEXT_H

#include "../indexed_context_node.h"

namespace Analysis::Structure::Context
{
    class LocalVariableContext final : public IndexedContextNode
    {
        public:
            LocalVariableContext(const Creation::Variable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
