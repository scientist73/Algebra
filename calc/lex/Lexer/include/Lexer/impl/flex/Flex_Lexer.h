#pragma once
#include "ILexer.h"
#include "FlexLexerGenerated.h"


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
                    ~Flex_Lexer() override;

                    void setupInputString(const std::string& str_input) override;
                    void closeInput() override;

                    INPUT getInputType() const override;
                    TokenType getNextToken() const override;
                private:
                    INPUT input_t;
                };
            } // namespace flex
        } // namespace lex
    } // namespace calc
} // namespace alg