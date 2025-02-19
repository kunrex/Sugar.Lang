#ifndef PROJECT_BINDER_H
#define PROJECT_BINDER_H

#include "../../../Parsing/ParseNodes/DataTypes/data_type_node.h"
#include "../../../Parsing/ParseNodes/Statements/import_statement_node.h"

#include "../../../Analysis/Structure/source_file.h"

namespace Analysis::Creation::Binding
{
    void CreateEnum(const ParseNodes::DataTypes::DataTypeNode* node, Structure::SourceFile* sourceFile);
    void CreateClass(const ParseNodes::DataTypes::DataTypeNode* node, Structure::SourceFile* sourceFile);
    void CreateStruct(const ParseNodes::DataTypes::DataTypeNode* node, Structure::SourceFile* sourceFile);

    void ImportStatement(const ParseNodes::Statements::ImportStatementNode* statement, Structure::SourceFile* sourceFile);
}

#endif
