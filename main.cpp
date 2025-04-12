#include "src/compiler.h"

int main()
{
    const auto source = "tests";

    const auto compiler = Compiler(source);
    compiler.Compile();

    return 0;
}
