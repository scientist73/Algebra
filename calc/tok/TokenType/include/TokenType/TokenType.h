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
            struct TokenType
            {
            public:
                constexpr explicit TokenType() : token_t(TOKEN::EMPTY) {}
                constexpr explicit TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                constexpr explicit TokenType(ParenTokenType&& paren) : token_t(TOKEN::PAREN), token(std::move(paren)) {}
                constexpr explicit TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                constexpr explicit TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}
                constexpr explicit TokenType(TerminationTokenType&& term) : token_t(TOKEN::TERMINATION), token(std::move(term)) {}

                //constexpr explicit TokenType(const TokenType& other);

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

        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

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