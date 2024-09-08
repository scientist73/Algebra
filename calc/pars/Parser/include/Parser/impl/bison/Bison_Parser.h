#pragma once
#include "IParser.h"
#include "BisonParserGenerated.h"


namespace alg
{
    namespace calc
    {
        namespace pars
        {
            namespace impl
            {
                namespace bison
                {
                    template<typename ScalarType>
                    class Bison_Parser : public IParser<ScalarType>
                    {
                    public:
                        Bison_Parser();
                        ~Bison_Parser() override = default;
                    
                        void pushToken(tok::TokenType token) override;
                        NumType<ScalarType> parse() override;
                    private:
                        parser par;
                    };
                } // namespace bison
            } // namespace impl
        } // namespace pars
    } // namespace calc
} // namespace alg


using namespace alg::calc::pars::impl::bison;

template<>
Bison_Parser<double>::Bison_Parser() : par() {}

template<>
void Bison_Parser<double>::pushToken(tok::TokenType token)
{
    alg::calc::pars::impl::bison::pushToken(token);
}
template<>
NumType<double> Bison_Parser<double>::parse()
{
    int res = par.parse();
    return getParseResult();
}
