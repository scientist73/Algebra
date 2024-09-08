#pragma once
#include "ILexer.h"
//#include "FlexLexerGenerated.h"


namespace alg
{
    namespace calc
    {
        namespace lex
        {
            namespace impl
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
                        TokenType yylex();

                        INPUT input_t;
                    };

                    /* This macro is used by flex to generate func body */
                    #define YY_DECL \
                    alg::calc::tok::TokenType alg::calc::lex::impl::flex::Flex_Lexer::yylex()

                } // namespace flex
            } // namespace impl
        } // namespace lex
    } // namespace calc
} // namespace alg