#include "src/compiler.h"

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main(std::string args[])
{
    const auto source = args->empty() ? std::string(fs::current_path()) : args[0];

    const auto compiler = Compiler(source);
    compiler.Compile();

    return 0;
}
