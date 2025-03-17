#include "invalid_indexer_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidIndexerExpression::InvalidIndexerExpression(const ContextNode* const operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType InvalidIndexerExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidIndexerExpression::SlotCount() const { return 0; }

    bool InvalidIndexerExpression::Readable() const { return false; }
    bool InvalidIndexerExpression::Writable() const { return false; }

    string InvalidIndexerExpression::CILData() const { return ""; }
}

