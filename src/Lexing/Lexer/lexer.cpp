#include "lexer.h"

#include <cfloat>
#include <vector>
#include <optional>

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Lexing/invalid_character_exception.h"
#include "../../Exceptions/Compilation/Lexing/character_expected_exception.h"
#include "../../Exceptions/Compilation/Lexing/constant_out_of_range_exception.h"

#include "../Tokens/Factories/keyword.h"
#include "../Tokens/Factories/constant.h"
#include "../Tokens/Factories/operator.h"
#include "../Tokens/Factories/separator.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens;
using namespace Tokens::Enums;

namespace Lexing
{
    Lexer::Lexer() : index(0), source(nullptr)
    { }

    Lexer& Lexer::Instance()
    {
        static Lexer instance;
        return instance;
    }

    char Lexer::LookAhead() const { return index == source->SourceLength() - 1 ? '\0' : source->SourceAt(index + 1); }

    void Lexer::ReadSingleLineComment()
    {
        while (index < source->SourceLength())
        {
            if (source->SourceAt(index) == '\n')
                break;

            index++;
        }
    }

    void Lexer::ReadMultiLineComment()
    {
        index += 2;

        while (index < source->SourceLength() - 1)
        {
            if (source->SourceAt(index) == '*')
                if (LookAhead() == '/')
                {
                    index++;
                    break;
                }

            index++;
        }
    }

    void Lexer::ReadNumber()
    {
        string number;
        const auto start = index;

        bool isWhole = true, breakOut = false;
        while (index < source->SourceLength())
        {
            switch (const char c = source->SourceAt(index))
            {
                case 's':
                    {
                        if (isWhole)
                        {
                            if (const auto converted = stol(number); converted < SHRT_MAX && converted > SHRT_MIN)
                            {
                                source->PushBackToken(Constant::Short(start, converted));
                                return;
                            }
                        }

                        source->PushBackToken(Token::Invalid(start, number));
                        ExceptionManager::Instance().AddChild(new ConstantOutOfRangeException(TypeKind::Short, index, source));
                        return;
                    }
                case 'i':
                    {
                        if (isWhole)
                        {
                            if (const auto converted = stol(number); converted < INT_MAX && converted > INT_MIN)
                            {
                                source->PushBackToken(Constant::Int(start, converted));
                                return;
                            }
                        }

                        source->PushBackToken(Token::Invalid(start, number));
                        ExceptionManager::Instance().AddChild(new ConstantOutOfRangeException(TypeKind::Int, index, source));
                        return;
                    }
                case 'l':
                    {
                        if (isWhole)
                        {
                            const auto converted = stol(number);
                            source->PushBackToken(Constant::Int(start, converted));
                        }
                        else
                        {
                            source->PushBackToken(Token::Invalid(start, number));
                            ExceptionManager::Instance().AddChild(new ConstantOutOfRangeException(TypeKind::Long, index, source));
                        }

                        return;
                    }
                case 'f':
                    {
                        if (const auto converted = stod(number); converted < FLT_MAX && converted > FLT_MIN)
                            source->PushBackToken(Constant::Float(start, converted));
                        else
                        {
                            source->PushBackToken(Token::Invalid(start, number));
                            ExceptionManager::Instance().AddChild(new ConstantOutOfRangeException(TypeKind::Float, index, source));
                        }
                    }
                    return;
                case 'd':
                    {
                        if (const auto converted = stod(number); converted < DBL_MAX && converted > DBL_MIN)
                            source->PushBackToken(Constant::Double(start, converted));
                        else
                        {
                            source->PushBackToken(Token::Invalid(start, number));
                            ExceptionManager::Instance().AddChild(new ConstantOutOfRangeException(TypeKind::Double, index, source));
                        }
                    }
                    return;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    number += c;
                    break;
                case '.':
                    {
                        if (isWhole)
                        {
                            number += '.';
                            isWhole = false;
                        }
                        else
                            breakOut = true;
                    }
                    break;
                case '-':
                    {
                        if (number.empty())
                            number += '-';
                        else
                            breakOut = true;
                    }
                    break;
                default:
                    breakOut = true;
                    break;
            }

            if (breakOut)
            {
                index--;
                break;
            }

            index++;
        }

        if (isWhole)
        {
            if (const auto converted = stol(number); converted < INT_MAX && converted > INT_MIN)
                source->PushBackToken(Constant::Int(start, converted));
            else
                source->PushBackToken(Constant::Long(start, converted));
        }
        else
        {
            if (const auto converted = stod(number); converted < FLT_MAX && converted > FLT_MIN)
                source->PushBackToken(Constant::Float(start, converted));
            else
                source->PushBackToken(Constant::Double(start, converted));
        }
    }

    void Lexer::ReadString()
    {
        index++;

        string value;
        const auto start = index;

        while(index < source->SourceLength())
        {
            switch(const char c = source->SourceAt(index))
            {
                case '\\':
                    {
                        value += '\\';

                        const char next = LookAhead();
                        value += next;
                        continue;
                    }
                case '"':
                    source->PushBackToken(Constant::String(start, value));
                    return;
                default:
                    value += c;
                    break;
            }

            index++;
        }

        source->PushBackToken(Token::Invalid(start, value));
        ExceptionManager::Instance().AddChild(new CharacterExpectedException('"', index - 1, source));
    }

    void Lexer::ReadIdentifier()
    {
        string value;
        const auto start = index;

        bool breakOut = false;
        while (index < source->SourceLength())
        {
            switch (const char c = source->SourceAt(index))
            {
                case '=':
                case '+':
                case '-':
                case '*':
                case '/':
                case ';':
                case ':':
                case '.':
                case ',':
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':
                case '<':
                case '>':
                case '&':
                case '|':
                case '!':
                case '^':
                case '~':
                case '?':
                case '%':
                case ' ':
                case '\n':
                case '\t':
                    breakOut = true;
                    break;
                case '"':
                case '\'':
                    source->PushBackToken(Token::Invalid(start, value));
                    ExceptionManager::Instance().AddChild(new InvalidCharacterException(c, index, source));
                    return;
                default:
                    value += c;
                    break;
            }

            if (breakOut)
            {
                index--;
                break;
            }

            index++;
        }

        if (const auto result = Keyword::TryMatchKeyword(value, start))
            source->PushBackToken(*result);
        else
            source->PushBackToken(Token::Identifier(start, value));
    }

    void Lexer::ReadCharacter()
    {
        index++;
        const auto start = index;

        if (source->SourceAt(index) == '\\')
            index++;

        if (LookAhead() == '\'')
        {
            source->PushBackToken(Constant::Character(start, source->SourceAt(index++)));
            return;
        }

        source->PushBackToken(Token::Invalid(start,  string(1, source->SourceAt(index))));
        ExceptionManager::Instance().AddChild(new CharacterExpectedException('\'', index, source));
    }

    void Lexer::Lex(Analysis::Structure::SourceFile* const source)
    {
        this->source = source;

        const auto length = source->SourceLength();

        for (index = 0; index < length; index++)
        {
            const char lookAhead = LookAhead();

            switch (source->SourceAt(index))
            {
                case ' ':
                case '\t':
                case '\n':
                    break;

                case '=':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::Equals(index++));
                        else
                            source->PushBackToken(Operator::Assignment(index));
                    }
                    break;
                case '!':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::NotEquals(index++));
                        else
                            source->PushBackToken(Operator::Not(index));
                    }
                    break;
                case '>':
                    {
                        if (lookAhead == '>')
                        {
                            index++;

                            if (LookAhead() == '=')
                                source->PushBackToken(Operator::AssignmentRightShift(index++));
                            else
                                source->PushBackToken(Operator::RightShift(index++));
                        }
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::GreaterThanEquals(index++));
                        else
                            source->PushBackToken(Operator::GreaterThan(index));
                    }
                    break;
                case '<':
                    {
                        if (lookAhead == '<')
                        {
                            index++;

                            if (LookAhead() == '=')
                                source->PushBackToken(Operator::AssignmentLeftShift(index++));
                            else
                                source->PushBackToken(Operator::LeftShift(index++));
                        }
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::LesserThanEquals(index++));
                        else
                            source->PushBackToken(Operator::LesserThan(index));
                    }
                    break;
                case '&':
                    {
                        if (lookAhead == '&')
                            source->PushBackToken(Operator::And(index++));
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentBitwiseAnd(index++));
                        else
                            source->PushBackToken(Operator::BitwiseAnd(index));
                    }
                    break;
                case '|':
                    {
                        if (lookAhead == '|')
                            source->PushBackToken(Operator::Or(index++));
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentBitwiseOr(index++));
                        else
                            source->PushBackToken(Operator::BitwiseOr(index));
                    }
                    break;
                case '^':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentBitwiseXor(index++));
                        else
                            source->PushBackToken(Operator::BitwiseXor(index));
                    }
                    break;
                case '~':
                    source->PushBackToken(Operator::BitwiseNot(index));
                    break;
                case '+':
                    {
                        if (lookAhead == '+')
                            source->PushBackToken(Operator::Increment(index++));
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentAddition(index++));
                        else
                        {
                            const auto prev = source->TokenCount() == 0 ? std::nullopt : std::make_optional(source->TokenAt(source->TokenCount() - 1));

                            if (isdigit(lookAhead))
                            {
                                if (!prev)
                                {
                                    ReadNumber();
                                    break;
                                }

                                switch (prev->Type())
                                {
                                    case TokenType::Constant:
                                    case TokenType::Identifier:
                                        source->PushBackToken(Operator::Addition(index));
                                        break;
                                    case TokenType::Separator:
                                        {
                                            if (prev->Kind() == SyntaxKind::CloseBracket || prev->Kind() == SyntaxKind::BoxCloseBracket)
                                                source->PushBackToken(Operator::Addition(index));
                                            else
                                            {
                                                index++;
                                                ReadNumber();
                                            }
                                        }
                                        break;
                                    default:
                                        {
                                            index++;
                                            ReadNumber();
                                        }
                                        break;
                                }
                            }
                            else
                            {
                                std::cout << !prev << std::endl;
                                if (!prev || lookAhead == '-')
                                {
                                    source->PushBackToken(Operator::Plus(index));
                                    break;
                                }

                                switch (prev->Type())
                                {
                                    case TokenType::Constant:
                                    case TokenType::Identifier:
                                        source->PushBackToken(Operator::Addition(index));
                                        break;
                                    case TokenType::Separator:
                                        {
                                            if (prev->Kind() == SyntaxKind::CloseBracket || prev->Kind() == SyntaxKind::BoxCloseBracket)
                                                source->PushBackToken(Operator::Addition(index));
                                            else
                                                source->PushBackToken(Operator::Plus(index));
                                        }
                                        break;
                                    default:
                                        source->PushBackToken(Operator::Plus(index));
                                        break;
                                }
                            }
                        }
                    }
                    break;
                case '-':
                    {
                        if (lookAhead == '-')
                            source->PushBackToken(Operator::Decrement(index++));
                        else if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentSubtraction(index++));
                        else
                        {
                            const auto prev = source->TokenCount() == 0 ? std::nullopt : std::make_optional(source->TokenAt(source->TokenCount() - 1));

                            if (isdigit(lookAhead))
                            {
                                if (!prev)
                                {
                                    ReadNumber();
                                    break;
                                }

                                switch (prev->Type())
                                {
                                    case TokenType::Constant:
                                    case TokenType::Identifier:
                                        source->PushBackToken(Operator::Subtraction(index));
                                        break;
                                    case TokenType::Separator:
                                        {
                                            if (prev->Kind() == SyntaxKind::CloseBracket || prev->Kind() == SyntaxKind::BoxCloseBracket)
                                                source->PushBackToken(Operator::Subtraction(index));
                                            else
                                                ReadNumber();
                                        }
                                        break;
                                    default:
                                        {
                                            index++;
                                            ReadNumber();
                                        }
                                    break;
                                }
                            }
                            else
                            {
                                if (!prev || lookAhead == '-')
                                {
                                    source->PushBackToken(Operator::Minus(index));
                                    break;
                                }

                                switch (prev->Type())
                                {
                                    case TokenType::Constant:
                                    case TokenType::Identifier:
                                        source->PushBackToken(Operator::Subtraction(index));
                                        break;
                                    case TokenType::Separator:
                                        {
                                            if (prev->Kind() == SyntaxKind::CloseBracket || prev->Kind() == SyntaxKind::BoxCloseBracket)
                                                source->PushBackToken(Operator::Subtraction(index));
                                            else
                                                source->PushBackToken(Operator::Minus(index));
                                        }
                                        break;
                                    default:
                                        source->PushBackToken(Operator::Minus(index));
                                    break;
                                }
                            }
                        }
                    }
                    break;
                case '*':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentMultiplication(index++));
                        else
                            source->PushBackToken(Operator::Multiplication(index));
                    }
                    break;
                case '/':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentDivision(index++));
                        else if (lookAhead == '/')
                            ReadSingleLineComment();
                        else if (lookAhead == '*')
                            ReadMultiLineComment();
                        else
                            source->PushBackToken(Operator::Division(index));
                    }
                    break;
                case '%':
                    {
                        if (lookAhead == '=')
                            source->PushBackToken(Operator::AssignmentModulus(index++));
                        else
                            source->PushBackToken(Operator::Modulus(index));
                    }
                    break;
                case ':':
                    source->PushBackToken(Separator::Colon(index));
                    break;
                case ';':
                    source->PushBackToken(Separator::Semicolon(index));
                    break;
                case '.':
                    source->PushBackToken(Separator::Dot(index));
                    break;
                case ',':
                    source->PushBackToken(Separator::Comma(index));
                    break;
                case '(':
                    source->PushBackToken(Separator::OpenBracket(index));
                    break;
                case ')':
                    source->PushBackToken(Separator::CloseBracket(index));
                    break;
                case '[':
                    source->PushBackToken(Separator::BoxOpenBracket(index));
                    break;
                case ']':
                    source->PushBackToken(Separator::BoxCloseBracket(index));
                    break;
                case '{':
                    source->PushBackToken(Separator::FlowerOpenBracket(index));
                    break;
                case '}':
                    source->PushBackToken(Separator::FlowerCloseBracket(index));
                    break;
                case '?':
                    source->PushBackToken(Separator::QuestionMark(index));
                    break;

                case '"':
                    ReadString();
                    break;
                case '\'':
                    ReadCharacter();
                    break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    ReadNumber();
                    break;

                default:
                    ReadIdentifier();
                    break;
            }
        }
    }
}
