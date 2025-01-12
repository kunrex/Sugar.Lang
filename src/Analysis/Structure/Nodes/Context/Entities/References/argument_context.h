#ifndef ARGUMENT_CONTEXT_H
#define ARGUMENT_CONTEXT_H

#include "../indexed_context_node.h"

namespace Analysis::Structure::Context
{
    class ArgumentContext final : public IndexedContextNode
    {
        public:
            ArgumentContext(const Creation::Variable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
