#include "TokenType.h"
#include <stdexcept>
#include <iostream>

using alg::calc::tok::TokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::IdentifierTokenType;
using alg::calc::tok::TerminationTokenType;


bool alg::calc::tok::operator==(const NumTokenType& l_op, const NumTokenType& r_op)
{
    return l_op.getNumTokenType() == r_op.getNumTokenType() && l_op.getScalar() == r_op.getScalar();
}
bool alg::calc::tok::operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op)
{ 
    return l_op.getOperatorTokenType() == r_op.getOperatorTokenType();
}
bool alg::calc::tok::operator==(const ParenTokenType& l_op, const ParenTokenType& r_op)
{
    return l_op.getParenTokenType() == r_op.getParenTokenType();
}
bool alg::calc::tok::operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op)
{ 
    return l_op.getIdentifier() == r_op.getIdentifier();
}
bool alg::calc::tok::operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op)
{ 
    return l_op.getTerminationTokenType() == r_op.getTerminationTokenType();
}

OperatorTokenType TokenType::getOperatorToken() const
{
    try
    { 
        return std::get<OperatorTokenType>(token); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getOperatorToken"); 
    }
}
ParenTokenType TokenType::getParenToken() const
{
    try
    { 
        return std::get<ParenTokenType>(token); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getParamToken"); 
    }
}
NumTokenType TokenType::getNumToken() const
{
    try
    { 
        return std::get<NumTokenType>(token); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getNumToken"); 
    }
}
IdentifierTokenType TokenType::getIdentifierToken() const
{
    try
    { 
        return std::get<IdentifierTokenType>(token); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getIdentifierToken"); 
    }
}
TerminationTokenType TokenType::getTerminationToken() const
{
    try
    { 
        return std::get<TerminationTokenType>(token); 
    } 
    catch(std::bad_variant_access& ex) 
    { 
        throw std::runtime_error("getTerminationToken"); 
    }
}


bool alg::calc::tok::operator==(const TokenType& l_op, const TokenType& r_op)
{
    if (l_op.getTokenType() == r_op.getTokenType())
    {
        switch (l_op.getTokenType())
        {
        case TokenType::TOKEN::IDENTIFIER:
            return l_op.getIdentifierToken() == r_op.getIdentifierToken();
        case TokenType::TOKEN::NUM:
            return l_op.getNumToken() == r_op.getNumToken();
        case TokenType::TOKEN::OPERATOR:
            return l_op.getOperatorToken() == r_op.getOperatorToken();
        case TokenType::TOKEN::TERMINATION:
            return l_op.getTerminationToken() == r_op.getTerminationToken();
        case TokenType::TOKEN::PAREN:
            return l_op.getParenToken() == r_op.getParenToken();
        }
    }
    else
        return false;
}