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
                constexpr explicit TokenType() : token_t(TOKEN::EMPTY) {}
                constexpr explicit TokenType(OperatorTokenType&& op_token) : token_t(TOKEN::OPERATOR), token(std::move(op_token)) {}
                constexpr explicit TokenType(ParenTokenType&& paren_token) : token_t(TOKEN::PAREN), token(std::move(paren_token)) {}
                constexpr explicit TokenType(NumTokenType&& num_token) : token_t(TOKEN::NUM), token(std::move(num_token)) {}
                constexpr explicit TokenType(IdentifierTokenType&& id_token) : token_t(TOKEN::IDENTIFIER), token(std::move(id_token)) {}
                constexpr explicit TokenType(TerminationTokenType&& term_token) : token_t(TOKEN::TERMINATION), token(std::move(term_token)) {}

                constexpr ~TokenType() = default;

                constexpr TOKEN getTokenType() const { return token_t; }
                
                constexpr bool isEmpty() const { return token_t == TOKEN::EMPTY; }
                constexpr const OperatorTokenType& getOperatorToken() const;
                constexpr const ParenTokenType& getParenToken() const;
                constexpr const NumTokenType& getNumToken() const;
                constexpr const IdentifierTokenType& getIdentifierToken() const;
                constexpr const TerminationTokenType& getTerminationToken() const;

            private:
                TOKEN token_t;
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

constexpr const OperatorTokenType& TokenType::getOperatorToken() const
{
    constexpr OperatorTokenType hdsa{OperatorTokenType::OPERATOR::DIV};

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