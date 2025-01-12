#ifndef BUILT_IN_INSTRUCTION_H
#define BUILT_IN_INSTRUCTION_H

#include <string>

namespace Analysis::Structure::Core
{
    class BuiltInInstruction
    {
        protected:
            std::string instruction;

            explicit BuiltInInstruction(std::string instruction);

        public:
            [[nodiscard]] const std::string& Instruction() const;
    };
}

#endif
