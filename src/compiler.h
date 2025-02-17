#ifndef COMPILER_H
#define COMPILER_H

#include <regex>

#include "Analysis/Structure/source_directory.h"

class Compiler
{
    private:
        const std::string sourcePath;
        Analysis::Structure::SourceDirectory* source;

        void PushDirectory(const std::string& strPath, Analysis::Structure::SourceDirectory* directory);

        void LexParse(Analysis::Structure::SourceObject* directory);

        void StructureDataTypes(const Analysis::Structure::SourceDirectory* directory);
        void ManageImportStatements(const Analysis::Structure::SourceDirectory* directory);

        void BindGlobal(const Analysis::Structure::SourceDirectory* directory);
        void BindLocal(const Analysis::Structure::SourceDirectory* directory);

    public:
        explicit Compiler(const std::string& sourcePath);

        void Compile();
};

#endif
