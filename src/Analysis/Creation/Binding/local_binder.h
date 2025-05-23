#ifndef LOCAL_BINDER_H
#define LOCAL_BINDER_H

#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Creation::Binding
{
    const Structure::Core::Interfaces::IContextNode* BindExpression(const ParseNodes::Core::Interfaces::IParseNode* expression, Structure::Core::Interfaces::IScoped* scoped, const Structure::Local::Scope* scope, const Structure::Core::Interfaces::IUserDefinedType* dataType);

    void BindScope(const ParseNodes::Core::Interfaces::IParseNode* scopeNode, Structure::Local::Scope* scope, Structure::Core::Interfaces::IScoped* scoped, const Structure::Core::Interfaces::IUserDefinedType* dataType);

    bool IsReturnComplete(const Structure::Local::Scope* scope, const Structure::Core::Interfaces::IDataType* expected);
}

#endif
