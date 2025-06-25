#include <filesystem>

#include "src/compiler.h"

namespace fs = std::filesystem;

int main(const int argc, char* argv[])
{
    const auto source = argc > 1 ? std::string(argv[1]) : std::string(fs::current_path());

    const Compiler compiler(source);
    compiler.Compile();

    return 0;
}
