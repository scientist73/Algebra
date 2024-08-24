#pragma once
#include <memory>
#include "ILexer.h"


namespace alg
{
    namespace calc
    {
        namespace lex
        {
            class Lexer
            {
            public:
                Lexer();
                
                void setupInputString(const std::string& str_input);
                void closeInput();

                ILexer::INPUT getInputType() const;
                TokenType getNextToken() const;
            private:
                enum class LEXER
                {
                    FLEX,
                };

                Lexer(LEXER lexer_t);

                std::unique_ptr<ILexer> lexer;
                LEXER lexer_t;
            };

        } // namespace lex
    } // namespace calc
} // namespace alg
