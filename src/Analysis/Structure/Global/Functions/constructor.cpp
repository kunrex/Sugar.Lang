#include "constructor.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"

#include "../../../../Parsing/ParseNodes/Groups/scope_node.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

const auto defaultConstructor = Tokens::Token(0, Tokens::Enums::TokenType::Constant, Tokens::Enums::SyntaxKind::Constant, 0.0);

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} instance void {} {}::{}{}", creationType->MemberType() == MemberType::Class ? "newobj" : "call", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void Constructor::Bind()
    {
        BindScoped(this);
    }

    DefaultConstructor::DefaultConstructor(const IDataType* const creationType) : Constructor(Describer::Public, creationType, new ScopeNode(defaultConstructor))
    { }

    DefaultConstructor::~DefaultConstructor()
    {
        delete parseNode;
    }
}

