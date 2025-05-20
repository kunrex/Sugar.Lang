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
#include "../ParseNodes/Groups/if_chain_node.h"

#include "../ParseNodes/Values/identifier_node.h"

#include "../ParseNodes/Properties/base_indexer_node.h"
#include "../ParseNodes/Properties/base_property_node.h"

#include "../ParseNodes/Expressions/indexer_expression_node.h"

#include "../ParseNodes/Functions/Calling/function_call_node.h"
#include "../ParseNodes/Functions/Creation/implicit_cast_node.h"
#include "../ParseNodes/Functions/Creation/explicit_cast_node.h"
#include "../ParseNodes/Functions/Creation/operator_overload_node.h"
#include "../ParseNodes/Functions/Creation/function_creation_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/input_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/print_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/invoke_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/format_node.h"
#include "../ParseNodes/Functions/Creation/constructor_creation_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/funcref_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/ref_call_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/tostring_node.h"
#include "../ParseNodes/Functions/Calling/BaseFunctions/copy_coll_node.h"

namespace Parsing
{
    class Parser final : public Services::SingletonService
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

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseEntity(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseExpression(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseNonEmptyExpression(Tokens::Enums::SeparatorKind breakSeparator);

            void ClearStack(const Tokens::Token& top, std::stack<const ParseNodes::Core::Interfaces::IParseNode*>& output);
            void ClearStack(std::stack<const Tokens::Token*>& stack, std::stack<const ParseNodes::Core::Interfaces::IParseNode*>& output);

            void ParseExpressionCollection(ParseNodes::DynamicNodeCollection* collection, Tokens::Enums::SeparatorKind breakSeparator);

            void ParseGeneric(ParseNodes::DynamicNodeCollection* generic);
            [[nodiscard]] const ParseNodes::Expressions::IndexerExpressionNode* ParseIndexerExpression(const ParseNodes::Core::Interfaces::IParseNode* operand);

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseType();
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* CheckType(const ParseNodes::Core::Interfaces::IParseNode* parsed) const;

            [[nodiscard]] const ParseNodes::Values::IdentifierNode* ParseIdentifier(bool increment = false);

            void ParseFunctionArguments(ParseNodes::DynamicNodeCollection* function);
            [[nodiscard]] const ParseNodes::Groups::CompoundDeclarationNode* ParseFunctionParameters();

            [[nodiscard]] const ParseNodes::Functions::Calling::RefCallNode* ParseRefCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::PrintNode* ParsePrintCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::InputNode* ParseInputCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::CopyCallNode* ParseCopyCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FormatNode* ParseFormatCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::InvokeNode* ParseInvokeCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::PrintlnNode* ParsePrintlnCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FuncRefNode* ParseFuncRefCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::ToStringNode* ParseToStringCall();

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseConstructorCall();
            [[nodiscard]] const ParseNodes::Functions::Calling::FunctionCallNode* ParseFunctionCall(const ParseNodes::Values::IdentifierNode* identifier);

            [[nodiscard]] std::tuple<const ParseNodes::Properties::GetNode*, const ParseNodes::Properties::SetNode*> ParseAccessors();
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseProperty(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::Core::Interfaces::IParseNode* type, const ParseNodes::Values::IdentifierNode* identifier);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseIndexer(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseConstructor(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseFunction(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::Core::Interfaces::IParseNode* type);

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseExplicitCast(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseImplicitCast(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseOperatorOverload(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Groups::IfChainNode* ParseIf();

            [[nodiscard]] const ParseNodes::Loops::WhileNode* ParseWhile();
            [[nodiscard]] const ParseNodes::Loops::DoWhileNode* ParseDoWhile();
            [[nodiscard]] const ParseNodes::Loops::ForLoopNode* ParseForLoop();

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseImportStatement();

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseEnumDefinition(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseClassDefinition(const ParseNodes::Describers::DescriberNode* describer);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseStructDefinition(const ParseNodes::Describers::DescriberNode* describer);

            [[nodiscard]] const ParseNodes::Describers::DescriberNode* ParseDescriber();

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseVariableDeclaration(const ParseNodes::Describers::DescriberNode* describer, const ParseNodes::Core::Interfaces::IParseNode* type, Tokens::Enums::SeparatorKind breakSeparator);

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseKeywordStatement(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseDescriberStatement(Tokens::Enums::SeparatorKind breakSeparator);
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseIdentifierStatement(Tokens::Enums::SeparatorKind breakSeparator);

            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseLazyScope();
            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseScope();
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseStatement();

        public:
            static Parser& Instance();

            [[nodiscard]] ParseNodes::Groups::SourceFileNode* Parse(const Analysis::Structure::SourceFile* source);
    };
}

#endif
