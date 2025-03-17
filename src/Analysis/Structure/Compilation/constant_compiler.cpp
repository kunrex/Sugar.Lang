#include "constant_compiler.h"

#include "../../../Parsing/ParseNodes/Constants/constant_node.h"

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Constants;

namespace Analysis::Structure::Compilation
{
    std::optional<CompilationResult> CompileExpression()
    {

    }

    std::optional<CompilationResult> CompileExpression(const ParseNode* const expressionNode, const SourceFile* const source)
    {
        switch (expressionNode->NodeType())
        {
            case NodeType::Unary:
                {

                }
            case NodeType::Binary:
                {

                }
            case NodeType::Dot:
                {

                }
            case NodeType::Constant:
                {
                    const auto constantNode = dynamic_cast<const ConstantNode*>(expressionNode);

                    constantNode.
                }
        }
    }
}
