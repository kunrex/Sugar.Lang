#include "parser.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/parsing_exception.h"

#include "../ParseNodes/DataTypes/enum_node.h"
#include "../ParseNodes/DataTypes/class_node.h"
#include "../ParseNodes/DataTypes/struct_node.h"

#include "../ParseNodes/Statements/import_statement_node.h"

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Groups;
using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Describers;
using namespace ParseNodes::Statements;

namespace Parsing
{
    const ParseNode* Parser::ParseImportStatement()
    {
        const auto keyword = Current();
        index++;

        const auto path = Current();
        if (TryMatchToken(path, SyntaxKind::Constant))
            if (const auto kind = static_cast<TypeKind>(path.Metadata()); kind != TypeKind::String)
                ExceptionManager::Instance().AddChild(new ParsingException("Local path expected (as a string).", path, source));

        TryMatchToken(Current(), SyntaxKind::Semicolon);
        return new ImportStatementNode(path);
    }

    const ParseNode* Parser::ParseEnumDefinition(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto identifier = ParseIdentifier(true);

        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);
        const auto body = new ScopeNode(source->TokenAt(index - 1));

        ParseExpressionCollection(body, SeparatorKind::FlowerCloseBracket);

        return new EnumNode(describer, identifier, body, keyword);
    }

    const ParseNode* Parser::ParseClassDefinition(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto identifier = ParseIdentifier(true);
        const auto body = ParseScope();

        return new ClassNode(describer, identifier, body, keyword);
    }

    const ParseNode* Parser::ParseStructDefinition(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto identifier = ParseIdentifier(true);
        const auto body = ParseScope();

        return new StructNode(describer, identifier, body, keyword);
    }
}