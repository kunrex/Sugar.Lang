#ifndef COMPILER_H
#define COMPILER_H

#include "Analysis/Structure/source_directory.h"

class Compiler
{
    private:
        std::string name;
        const std::string sourcePath;

        mutable Analysis::Structure::SourceDirectory* source;

        void Transpile() const;

    public:
        explicit Compiler(const std::string& sourcePath);

        void Compile() const;
};

#endif
