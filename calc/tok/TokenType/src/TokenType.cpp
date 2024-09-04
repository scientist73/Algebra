#include "TokenType.h"


bool alg::calc::tok::operator==(const NumTokenType& l_op, const NumTokenType& r_op)
{
    return l_op.getNumTokenType() == r_op.getNumTokenType() && l_op.getScalar() == r_op.getScalar();
}
bool alg::calc::tok::operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op)
{ 
    return l_op.getOperatorTokenType() == r_op.getOperatorTokenType();
}
bool alg::calc::tok::operator==(const ParamTokenType& l_op, const ParamTokenType& r_op)
{
    return l_op.getParamTokenType() == r_op.getParamTokenType();
}
bool alg::calc::tok::operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op)
{ 
    return l_op.getIdentifier() == r_op.getIdentifier();
}
bool alg::calc::tok::operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op)
{ 
    return l_op.getTerminationTokenType() == r_op.getTerminationTokenType();
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
        case TokenType::TOKEN::PARAM:
            return l_op.getParamToken() == r_op.getParamToken();
        }
    }
    else
        return false;
}