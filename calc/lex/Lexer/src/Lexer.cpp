#include "Lexer.h"
#include "Flex_Lexer.h"

using namespace alg::calc::lex;

Lexer::Lexer() :
    Lexer(LEXER::FLEX)
{}

void Lexer::setupInputString(const std::string& str_input)
{
    return lexer->setupInputString(str_input);
}
void Lexer::closeInput()
{
    return lexer->closeInput();
}

ILexer::INPUT Lexer::getInputType() const
{
    return lexer->getInputType();
}
TokenType Lexer::getNextToken() const
{
    return lexer->getNextToken();
}

Lexer::Lexer(LEXER lexer_t) : 
    lexer_t(lexer_t), lexer(nullptr)
{
    switch (lexer_t)
    {
    case LEXER::FLEX:
        lexer.reset(new flex::Flex_Lexer());
        break;
    }
}