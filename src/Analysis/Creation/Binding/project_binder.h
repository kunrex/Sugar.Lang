#ifndef PROJECT_BINDER_H
#define PROJECT_BINDER_H

#include "../../../Analysis/Structure/source_file.h"

namespace Analysis::Creation::Binding
{
    void CreateEnum(const ParseNodes::Core::Interfaces::IParseNode* node, Structure::SourceFile* sourceFile);
    void CreateClass(const ParseNodes::Core::Interfaces::IParseNode* node, Structure::SourceFile* sourceFile);
    void CreateStruct(const ParseNodes::Core::Interfaces::IParseNode* node, Structure::SourceFile* sourceFile);

    void ImportStatement(const ParseNodes::Core::Interfaces::IParseNode* statement, Structure::SourceFile* sourceFile);
}

#endif
