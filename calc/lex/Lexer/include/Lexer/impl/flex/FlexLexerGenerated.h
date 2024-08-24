#pragma once
#include "TokenType.h"

namespace alg
{
    namespace calc
    {
        namespace lex
        {
            namespace flex
            {
                #define YY_DECL \
                alg::calc::tok::TokenType yylex()
                //YY_DECL;
                alg::calc::tok::TokenType yylex();
            } // namespace flex
        } // namespace lex
    } // namespace calc
} // namespace alg
