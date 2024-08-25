#pragma once
#include "ILexer.h"
//#include "FlexLexerGenerated.h"


namespace alg
{
    namespace calc
    {
        namespace lex
        {
            namespace flex
            {
                class Flex_Lexer : public ILexer
                {
                public:
                    Flex_Lexer();
                    ~Flex_Lexer() override = default;

                    void setupInputString(const std::string& str_input) override;
                    void closeInput() override;

                    INPUT getInputType() const override;
                    TokenType getNextToken() override;
                private:
                    INPUT input_t;
                };

                /* This macro is used by flex to generate func body */
                #define YY_DECL \
                alg::calc::tok::TokenType alg::calc::lex::flex::Flex_Lexer::getNextToken()

            } // namespace flex
        } // namespace lex
    } // namespace calc
} // namespace alg