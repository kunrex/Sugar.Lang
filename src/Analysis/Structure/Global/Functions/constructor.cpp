#include "constructor.h"

#include <format>

#include "function_extensions.h"
#include "../../../../Parsing/ParseNodes/Groups/scope_node.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const IDataType* const creationType, const NodeCollection<ParseNodes::ParseNode>* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call instance void {} {}::{}{}", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    DefaultConstructor::DefaultConstructor(const IDataType* const creationType) : Constructor(Describer::Public, creationType, new ScopeNode(0))
    { }

    DefaultConstructor::~DefaultConstructor()
    {
        delete parseNode;
    }

    StaticConstructor::StaticConstructor(const IDataType* const creationType) : Constructor(Describer::Private | Describer::Static, creationType, nullptr)
    { }

    InstanceConstructor::InstanceConstructor(const IDataType* const creationType) : Constructor(Describer::Private, creationType, nullptr)
    { }
}

