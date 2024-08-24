#include "TokenGenerator.h"

using namespace alg::calc::tok;

TokenType TokenGenerator::constructOperatorToken(OperatorTokenType&& op_token)
{
    return TokenType(std::move(op_token));
}
TokenType TokenGenerator::constructNumTokenToken(NumTokenType&& num_token)
{
    return TokenType(std::move(num_token));
}
TokenType TokenGenerator::constructIdentifierToken(IdentifierTokenType&& id_token)
{
    return TokenType(std::move(id_token));   
}
TokenType TokenGenerator::constructTerminationToken(TerminationTokenType&& term_token)
{
    return TokenType(std::move(term_token));
}