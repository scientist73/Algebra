#include "TokenGenerator.h"

using namespace alg::calc::tok;

TokenType TokenGenerator::constructOperator(OperatorTokenType::OPERATOR op_t)
{
    return TokenType(OperatorTokenType(op_t));
}
TokenType TokenGenerator::constructParam(ParamTokenType::PARAM param_t)
{
    return TokenType(ParamTokenType(param_t));
}
TokenType TokenGenerator::constructNumToken(NumTokenType::NUM num_t, const std::string& scalar)
{
    return TokenType(NumTokenType(num_t, scalar));
}
TokenType TokenGenerator::constructIdentifier(const std::string& id)
{
    return TokenType(IdentifierTokenType(id));
}
TokenType TokenGenerator::constructTermination(TerminationTokenType::TERMINATION term_t)
{
    return TokenType(TerminationTokenType(term_t));
}