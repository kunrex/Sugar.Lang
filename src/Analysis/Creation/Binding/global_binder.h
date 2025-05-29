#ifndef GLOBAL_BINDER_H
#define GLOBAL_BINDER_H

#include "../../Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../Parsing/ParseNodes/Core/Interfaces/i_parse_node.h"
#include "../../Structure/DataTypes/enum.h"

namespace Analysis::Creation::Binding
{
    void BindEnumConstant(const ParseNodes::Core::Interfaces::IParseNode* expressionNode, Structure::DataTypes::Enum* dataType);

    void DeclareGlobalVariable(const ParseNodes::Core::Interfaces::IParseNode* declarationNode, Structure::Core::Interfaces::IUserDefinedType* dataType);
    void InitialiseGlobalVariable(const ParseNodes::Core::Interfaces::IParseNode* initialisationNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateProperty(const ParseNodes::Core::Interfaces::IParseNode* propertyNode, Structure::Core::Interfaces::IUserDefinedType* dataType);
    void InitialiseProperty(const ParseNodes::Core::Interfaces::IParseNode* propertyNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateIndexer(const ParseNodes::Core::Interfaces::IParseNode* indexerNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateFunction(const ParseNodes::Core::Interfaces::IParseNode* functionCreationNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateConstructor(const ParseNodes::Core::Interfaces::IParseNode* constructorCreationNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateExplict(const ParseNodes::Core::Interfaces::IParseNode* explicitCastNode, Structure::Core::Interfaces::IUserDefinedType* dataType);
    void CreateImplicit(const ParseNodes::Core::Interfaces::IParseNode* implicitCastNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void CreateOperatorOverload(const ParseNodes::Core::Interfaces::IParseNode* operatorOverloadNode, Structure::Core::Interfaces::IUserDefinedType* dataType);

    void TryDeclareExplicitString(Structure::Core::Interfaces::IUserDefinedType* dataType);
    void TryDeclareStaticConstructor(Structure::Core::Interfaces::IUserDefinedType* dataType);
    void TryDeclareDefaultConstructor(Structure::Core::Interfaces::IUserDefinedType* dataType);
}

#endif
