#ifndef COMPILER_H
#define COMPILER_H

#include <regex>

#include "Analysis/Structure/source_directory.h"

class Compiler
{
    private:
        mutable std::string name;
        const std::string sourcePath;

        mutable Analysis::Structure::SourceDirectory* source;

    public:
        explicit Compiler(const std::string& sourcePath);

        void Compile() const;
};

#endif
