#ifndef PROJECT_BINDER_H
#define PROJECT_BINDER_H

#include "../../../Parsing/ParseNodes/Statements/import_statement_node.h"

#include "../../Structure/source_directory.h"
#include "../../../Analysis/Structure/source_file.h"

namespace Analysis
{
    void ImportStatement(const ParseNodes::Statements::ImportStatementNode* statement, Structure::SourceFile* sourceFile);
}

#endif
