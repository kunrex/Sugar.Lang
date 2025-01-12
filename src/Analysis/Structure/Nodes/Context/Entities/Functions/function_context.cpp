#include "function_context.h"

#include "../../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    FunctionContext::FunctionContext(const FunctionDefinition* function) : ContextNode(function->CreationType()), function(function)
    { }

    std::string FunctionContext::InstructionGet() const { return std::format("call {}{} {}{}", function->CheckDescriber(Describer::Static) ? "" : "instance ", function->CreationType()->FullName(), function->FullName(), function->SignatureString()); }
    std::string FunctionContext::InstructionSet() const { return ""; }

    bool FunctionContext::IsStatic() const { return function->CheckDescriber(Describer::Static); }

    int FunctionContext::SlotCount() const
    {
        int current = 0, maxCount = 0;
        for (const auto child : children)
        {
            if (const auto c = std::max(child->SlotCount(), child->CreationType()->SlotCount()); current + c > maxCount)
                maxCount = current + c;

            current += child->CreationType()->SlotCount();
        }

        auto result = maxCount + !function->CheckDescriber(Describer::Static);
        if (result == 0 and function->CreationType() != nullptr)
            result = 1;

        return result;
    }
}

