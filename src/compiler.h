#ifndef COMPILER_H
#define COMPILER_H

#include "Analysis/Structure/source_directory.h"

class Compiler
{
    private:
        Analysis::Structure::SourceDirectory* source;

        void PushDirectory(const std::string& strPath, Analysis::Structure::SourceDirectory* directory);

        void LexParse(Analysis::Structure::SourceObject* directory);

    public:
        explicit Compiler(const std::string& sourcePath);

        void Compile();
};

#endif
