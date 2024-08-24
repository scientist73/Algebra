#pragma once
#include <memory>
#include "IParser.h"



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

                NumType<ScalarType> parseString(const std::string& str_input);
            private:
                enum class PARSER
                {
                    BISON,
                };
                Parser(PARSER parser_t);

                std::unique_ptr<IParser> parser;
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
NumType<ScalarType> Parser<ScalarType>::parseString(const std::string& str_input)
{
    return parser->parseString(str_input);
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