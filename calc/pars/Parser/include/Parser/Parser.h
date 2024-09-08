#pragma once
#include <memory>
#include "IParser.h"
#include "TokenType.h"

using alg::calc::tok::TokenType;

namespace alg
{
    namespace calc
    {
        namespace pars
        {
            template<typename ScalarType>
            class Parser
            {
            public:
                Parser();

                void pushToken(TokenType token);
                NumType<ScalarType> parse();
            private:
                enum class PARSER
                {
                    BISON,
                };
                Parser(PARSER parser_t);

                std::unique_ptr<IParser<ScalarType>> parser;
                PARSER parser_t;
            };

        } // namespace pars
    } // namespace calc
} // namespace alg


#include "Bison_Parser.h"

using namespace alg::calc::pars;

template<typename ScalarType>
Parser<ScalarType>::Parser() : Parser(PARSER::BISON)
{}

template<typename ScalarType>
void Parser<ScalarType>::pushToken(TokenType token)
{
    return parser->pushToken(token);
}
template<typename ScalarType>
NumType<ScalarType> Parser<ScalarType>::parse()
{
    return parser->parse();
}

template<typename ScalarType>
Parser<ScalarType>::Parser(PARSER parser_t) :
    parser_t(parser_t), parser(nullptr)
{
    switch (parser_t)
    {
    case PARSER::BISON:
        parser.reset(new Bison_Parser<ScalarType>());
        break;
    }
}