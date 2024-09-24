#pragma once
#include "ITokenType.h"
#include "IdentifierTokenType.h"
#include "NumTokenType.h"
#include "OperatorTokenType.h"
#include "ParenTokenType.h"
#include "TerminationTokenType.h"
#include "TokenTypeException.h"
#include <optional>
#include <string>
#include <stdexcept>
#include <variant>
#include <cassert>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            template<typename SpecificTokenType>
            concept IsSpecificTokenType = 
                std::is_same<SpecificTokenType, OperatorTokenType>::value ||
                std::is_same<SpecificTokenType, ParenTokenType>::value ||
                std::is_same<SpecificTokenType, NumTokenType>::value ||
                std::is_same<SpecificTokenType, IdentifierTokenType>::value ||
                std::is_same<SpecificTokenType, TerminationTokenType>::value;
                
            class TokenType
            {
            public:
                constexpr explicit TokenType();
                template<typename SpecificTokenType> requires IsSpecificTokenType<SpecificTokenType>
                constexpr explicit TokenType(SpecificTokenType&& op_token);

                template<typename SpecificTokenType> requires IsSpecificTokenType<SpecificTokenType>
                friend constexpr const SpecificTokenType& get_token(const TokenType& token);
                constexpr TOKEN getTokenType() const noexcept;
                constexpr bool isEmpty() const noexcept;

            private:
                std::optional<std::variant<OperatorTokenType, ParenTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType>> token;
            };

            template<typename SpecificTokenType> requires IsSpecificTokenType<SpecificTokenType>
            constexpr const SpecificTokenType& get_token(const TokenType& token);
            template<typename SpecificTokenType, typename... Args> requires IsSpecificTokenType<SpecificTokenType>
            constexpr TokenType make_token(Args&&... args);

            constexpr bool operator==(const TokenType& l_op, const TokenType& r_op);
            constexpr bool operator!=(const TokenType& l_op, const TokenType& r_op);

        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr TokenType::TokenType()
{}
template<typename SpecificTokenType> requires IsSpecificTokenType<SpecificTokenType>
constexpr TokenType::TokenType(SpecificTokenType&& specific_token) :
    token(std::forward<SpecificTokenType>(specific_token))
{}

constexpr TOKEN TokenType::getTokenType() const noexcept
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
        }
    }
    else
        return TOKEN::EMPTY;

    assert(false);
}

constexpr bool TokenType::isEmpty() const noexcept
{
    return getTokenType() == TOKEN::EMPTY;
}

template<typename SpecificTokenType> requires IsSpecificTokenType<SpecificTokenType>
constexpr const SpecificTokenType& alg::calc::tok::get_token(const TokenType& token)
{
    try
    { 
        return std::get<SpecificTokenType>(token.token.value());
    } 
    catch(std::bad_variant_access const& ex)
    {
        throw except::token_value_has_different_type(token.getTokenType());
    }
}
template<typename SpecificTokenType, typename... Args> requires IsSpecificTokenType<SpecificTokenType>
constexpr TokenType alg::calc::tok::make_token(Args&&... args)
{
    return TokenType(SpecificTokenType(args...));
}


constexpr bool alg::calc::tok::operator==(const TokenType& l_op, const TokenType& r_op)
{
    if (l_op.getTokenType() == r_op.getTokenType())
    {
        switch (l_op.getTokenType())
        {
        case TOKEN::IDENTIFIER:
            return get_token<IdentifierTokenType>(l_op) == get_token<IdentifierTokenType>(r_op);
        case TOKEN::NUM:
            return get_token<NumTokenType>(l_op) == get_token<NumTokenType>(r_op);
        case TOKEN::OPERATOR:
            return get_token<OperatorTokenType>(l_op) == get_token<OperatorTokenType>(r_op);
        case TOKEN::TERMINATION:
            return get_token<TerminationTokenType>(l_op) == get_token<TerminationTokenType>(r_op);
        case TOKEN::PAREN:
            return get_token<ParenTokenType>(l_op) == get_token<ParenTokenType>(r_op);
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

