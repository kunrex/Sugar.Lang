#include "overloaded_indexer_expression.h"

#include "../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    OverloadedIndexerExpression::OverloadedIndexerExpression(const IndexerDefinition* indexer, const ContextNode* operand) : UnaryContextNode(indexer->CreationType(), operand), indexer(indexer)
    { }

    std::string OverloadedIndexerExpression::InstructionGet() const { return std::format("call instance {} {}::{}{}", indexer->CreationType()->FullName(), indexer->Parent()->FullName(), get_indexer, indexer->SignatureString()); }
    std::string OverloadedIndexerExpression::InstructionSet() const { return std::format("call instance void {}::{}{}", indexer->Parent()->FullName(), set_indexer, indexer->SignatureStringSet()); }
}


