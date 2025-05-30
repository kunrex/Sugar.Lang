#ifndef INVALID_INDEXER_EXPRESSION_H
#define INVALID_INDEXER_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class InvalidIndexerExpression final : public DynamicContextCollection
    {
        public:
            explicit InvalidIndexerExpression(const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
