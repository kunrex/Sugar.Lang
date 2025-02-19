#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <optional>
#include <functional>

#include "../../Services/singleton_service.h"

#include "../../Analysis/Structure/source_file.h"

#include "../../Lexing/Tokens/token.h"

#include "../ParseNodes/parse_node.h"
#include "../ParseNodes/invalid_node.h"

#include "../ParseNodes/Loops/while_node.h"
#include "../ParseNodes/Loops/do_while_node.h"
#include "../ParseNodes/Loops/for_loop_node.h"

#include "../ParseNodes/Groups/scope_node.h"
#include "../ParseNodes/Groups/generic_node.h"
#include "../ParseNodes/Groups/if_chain_node.h"

#include "../ParseNodes/Values/identifier_node.h"

#include "../ParseNodes/Properties/base_indexer_node.h"
#include "../ParseNodes/Properties/base_property_node.h"

#include "../ParseNodes/Expressions/indexer_expression_node.h"

#include "../ParseNodes/Functions/Calling/function_call_node.h"
#include "../ParseNodes/Functions/Creation/implicit_cast_node.h"
#include "../ParseNodes/Functions/Creation/explicit_cast_node.h"
#include "../ParseNodes/Functions/Calling/constructor_call_node.h"
#include "../ParseNodes/Functions/Creation/operator_overload_node.h"
#include "../ParseNodes/Functions/Creation/function_creation_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/input_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/print_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/format_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/funcref_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/invoke_node.h"
#include "../ParseNodes/Functions/Creation/constructor_creation_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/tostring_node.h"

namespace Parsing
{
    class Parser final : public Services::SingletonService<Parser>
    {
        private:
            unsigned long index = 0;
            Analysis::Structure::SourceFile* source = nullptr;

            [[nodiscard]] const Tokens::Token& Current() const;
            [[nodiscard]] std::optional<std::reference_wrapper<Tokens::Token>> LookAhead() const;

            [[nodiscard]] bool MatchType(const Tokens::Token& token, Tokens::Enums::TokenType tokenType, bool increment = false);
            [[nodiscard]] bool MatchToken(const Tokens::Token& token, Tokens::Enums::SyntaxKind syntaxKind, bool increment = false);
            [[nodiscard]] bool MatchSeparator(const Tokens::Token& token, Tokens::Enums::SeparatorKind separatorKind, bool increment = false);

            [[nodiscard]] bool MatchLookAhead(Tokens::Enums::TokenType tokenType, bool increment = false);
            [[nodiscard]] bool MatchLookAhead(Tokens::Enums::SyntaxKind syntaxKind, bool increment = false);
            [[nodiscard]] bool MatchLookAhead(Tokens::Enums::SeparatorKind separatorKind, bool increment = false);

            bool TryMatchType(const Tokens::Token& token, Tokens::Enums::TokenType tokenType, bool increment = false);
            bool TryMatchToken(const Tokens::Token& token, Tokens::Enums::SyntaxKind syntaxKind, bool increment = false);
            bool TryMatchSeparator(const Tokens::Token& token, Tokens::Enums::SeparatorKind kind, bool increment = false);

            [[nodiscard]] ParseNodes::InvalidNode* ParseInvalid(Tokens::Enums::SeparatorKind breakOut);

            [[nodiscard]] const ParseNodes::ParseNode* ParseEntity(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::ParseNode* ParseExpression(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::ParseNode* ParseNonEmptyExpression(Tokens::Enums::SeparatorKind breakSeparator);

            void ClearStack(const Tokens::Token& top, std::stack<const ParseNodes::ParseNode*>& output);
            void ClearStack(std::stack<const Tokens::Token*>& stack, std::stack<const ParseNodes::ParseNode*>& output);

            [[nodiscard]] const ParseNodes::Groups::GenericNode* ParseGeneric();
            [[nodiscard]] const ParseNodes::Expressions::IndexerExpressionNode* ParseIndexerExpression(const ParseNodes::ParseNode* operand);

            [[nodiscard]] const ParseNodes::ParseNode* ParseType();
            [[nodiscard]] const ParseNodes::ParseNode* CheckType(const ParseNodes::ParseNode* parsed) const;

            [[nodiscard]] const ParseNodes::Values::IdentifierNode* ParseIdentifier(bool increment = false);

            void ParseFunctionArguments(ParseNodes::NodeCollection<ParseNodes::ParseNode>* function);
            [[nodiscard]] const ParseNodes::Groups::CompoundDeclarationNode* ParseFunctionParameters();

            [[nodiscard]] const ParseNodes::Functions::Calling::PrintNode* ParsePrintCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::InputNode* ParseInputCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FormatNode* ParseFormatCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::InvokeNode* ParseInvokeCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::PrintlnNode* ParsePrintlnCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FuncRefNode* ParseFuncRefCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::ToStringNode* ParseToStringCall();

            [[nodiscard]] const ParseNodes::Functions::Calling::ConstructorCallNode* ParseConstructorCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FunctionCallNode* ParseFunctionCall(const ParseNodes::Values::IdentifierNode* identifier);

            [[nodiscard]] const ParseNodes::Properties::BasePropertyNode* ParseProperty(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::ParseNode* type, const ParseNodes::Values::IdentifierNode* identifier);
            [[nodiscard]] const ParseNodes::Properties::BaseIndexerNode* ParseIndexer(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Functions::Creation::ConstructorCreationNode* ParseConstructor(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Functions::Creation::FunctionCreationNode* ParseFunction(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::ParseNode* type);

            [[nodiscard]] const ParseNodes::Functions::Creation::ExplicitCastNode* ParseExplicitCast(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Functions::Creation::ImplicitCastNode* ParseImplicitCast(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Functions::Creation::OperatorOverloadNode* ParseOperatorOverload(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Groups::IfChainNode* ParseIf();

            [[nodiscard]] const ParseNodes::Loops::WhileNode* ParseWhile();
            [[nodiscard]] const ParseNodes::Loops::DoWhileNode* ParseDoWhile();
            [[nodiscard]] const ParseNodes::Loops::ForLoopNode* ParseForLoop();

            [[nodiscard]] const ParseNodes::ParseNode* ParseImportStatement();

            [[nodiscard]] const ParseNodes::ParseNode* ParseEnumDefinition(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::ParseNode* ParseClassDefinition(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::ParseNode* ParseStructDefinition(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Describers::DescriberNode* ParseDescriber();

            [[nodiscard]] const ParseNodes::ParseNode* ParseVariableDeclaration(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::ParseNode* type, Tokens::Enums::SeparatorKind breakSeparator);

            [[nodiscard]] const ParseNodes::ParseNode* ParseKeywordStatement(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::ParseNode* ParseDescriberStatement(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::ParseNode* ParseIdentifierStatement(Tokens::Enums::SeparatorKind breakSeparator);

            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseLazyScope();
            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseScope();
            [[nodiscard]] const ParseNodes::ParseNode* ParseStatement();

        public:
            void Parse(Analysis::Structure::SourceFile* source);
    };
}

#endif
