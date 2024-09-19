#pragma once
#include "ITokenType.h"
#include "IdentifierTokenType.h"
#include "NumTokenType.h"
#include "OperatorTokenType.h"
#include "ParenTokenType.h"
#include "TerminationTokenType.h"
#include <optional>
#include <string>
#include <stdexcept>
#include <variant>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class TokenType
            {
            public:
                constexpr explicit TokenType();
                constexpr explicit TokenType(OperatorTokenType&& op_token);
                constexpr explicit TokenType(ParenTokenType&& paren_token);
                constexpr explicit TokenType(NumTokenType&& num_token);
                constexpr explicit TokenType(IdentifierTokenType&& id_token);
                constexpr explicit TokenType(TerminationTokenType&& term_token);

                constexpr TOKEN getTokenType() const;
                
                constexpr bool isEmpty() const;
                constexpr const OperatorTokenType& getOperatorToken() const;
                constexpr const ParenTokenType& getParenToken() const;
                constexpr const NumTokenType& getNumToken() const;
                constexpr const IdentifierTokenType& getIdentifierToken() const;
                constexpr const TerminationTokenType& getTerminationToken() const;

            private:
                std::optional<std::variant<OperatorTokenType, ParenTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType>> token;
            };

            constexpr bool operator==(const TokenType& l_op, const TokenType& r_op);
            constexpr bool operator!=(const TokenType& l_op, const TokenType& r_op);

            constexpr TokenType makeIdentifierToken(std::string_view id);
            constexpr TokenType makeNumToken(NumTokenType::NUM num_t, std::string_view scalar);
            constexpr TokenType makeOperatorToken(OperatorTokenType::OPERATOR operator_t);
            constexpr TokenType makeParenToken(ParenTokenType::PAREN paren_t);
            constexpr TokenType makeTerminationToken(TerminationTokenType::TERMINATION term_t);

        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr TokenType::TokenType()
{}
constexpr TokenType::TokenType(OperatorTokenType&& op_token) :
    token(std::move(op_token))
{}
constexpr TokenType::TokenType(ParenTokenType&& paren_token) :
    token(std::move(paren_token))
{}
constexpr TokenType::TokenType(NumTokenType&& num_token) :
    token(std::move(num_token))
{}
constexpr TokenType::TokenType(IdentifierTokenType&& id_token) :
    token(std::move(id_token))
{}
constexpr TokenType::TokenType(TerminationTokenType&& term_token) :
    token(std::move(term_token))
{}

constexpr TOKEN TokenType::getTokenType() const
{ 
    if (token.has_value())
    {
        switch (token.value().index())
        {
        case 0:
            return TOKEN::OPERATOR;
        case 1:
            return TOKEN::PAREN;
        case 2:
            return TOKEN::NUM;
        case 3:
            return TOKEN::IDENTIFIER;
        case 4:
            return TOKEN::TERMINATION;
        default:
            throw std::runtime_error("");
        }
    }
    else
        return TOKEN::EMPTY;

}

constexpr bool TokenType::isEmpty() const
{
    return getTokenType() == TOKEN::EMPTY;
}
constexpr const OperatorTokenType& TokenType::getOperatorToken() const
{
    try
    { 
        return std::get<OperatorTokenType>(token.value()); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getOperatorToken"); 
    }
}
constexpr const ParenTokenType& TokenType::getParenToken() const
{
    try
    { 
        return std::get<ParenTokenType>(token.value()); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getParamToken"); 
    }
}
constexpr const NumTokenType& TokenType::getNumToken() const
{
    try
    { 
        return std::get<NumTokenType>(token.value()); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getNumToken"); 
    }
}
constexpr const IdentifierTokenType& TokenType::getIdentifierToken() const
{
    try
    { 
        return std::get<IdentifierTokenType>(token.value()); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getIdentifierToken"); 
    }
}
constexpr const TerminationTokenType& TokenType::getTerminationToken() const
{
    try
    { 
        return std::get<TerminationTokenType>(token.value()); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getTerminationToken"); 
    }
}

constexpr bool alg::calc::tok::operator==(const TokenType& l_op, const TokenType& r_op)
{
    if (l_op.getTokenType() == r_op.getTokenType())
    {
        switch (l_op.getTokenType())
        {
        case TOKEN::IDENTIFIER:
            return l_op.getIdentifierToken() == r_op.getIdentifierToken();
        case TOKEN::NUM:
            return l_op.getNumToken() == r_op.getNumToken();
        case TOKEN::OPERATOR:
            return l_op.getOperatorToken() == r_op.getOperatorToken();
        case TOKEN::TERMINATION:
            return l_op.getTerminationToken() == r_op.getTerminationToken();
        case TOKEN::PAREN:
            return l_op.getParenToken() == r_op.getParenToken();
        case TOKEN::EMPTY:
            return true;
        }
    }
    else
        return false;
}
constexpr bool alg::calc::tok::operator!=(const TokenType& l_op, const TokenType& r_op)
{
    return !(l_op == r_op);
}

constexpr TokenType alg::calc::tok::makeIdentifierToken(std::string_view id)
{
    return TokenType(IdentifierTokenType(id));
}
constexpr TokenType alg::calc::tok::makeNumToken(NumTokenType::NUM num_t, std::string_view scalar)
{
    return TokenType(NumTokenType(num_t, scalar));
}
constexpr TokenType alg::calc::tok::makeOperatorToken(OperatorTokenType::OPERATOR operator_t)
{
    return TokenType(OperatorTokenType(operator_t));
}
constexpr TokenType alg::calc::tok::makeParenToken(ParenTokenType::PAREN paren_t)
{
    return TokenType(ParenTokenType(paren_t));
}
constexpr TokenType alg::calc::tok::makeTerminationToken(TerminationTokenType::TERMINATION term_t)
{
    return TokenType(TerminationTokenType(term_t));
}