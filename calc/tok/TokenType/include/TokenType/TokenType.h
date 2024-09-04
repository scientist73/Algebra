#pragma once
#include <optional>
#include <string>
#include <stdexcept>
#include <variant>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            struct NumTokenType
            {
            public:
                enum class NUM
                {
                    REAL,
                    IMAG,
                };

                NumTokenType(NUM num_t, const std::string& scalar) : num_t(num_t), scalar(scalar) {}

                NUM getNumTokenType() const { return num_t; }
                std::string getScalar() const { return scalar; }

            private:
                NUM num_t;
                std::string scalar;
            };
            bool operator==(const NumTokenType& l_op, const NumTokenType& r_op);


            struct OperatorTokenType
            {
            public:
                enum class OPERATOR
                {
                    PLUS,
                    MINUS,
                    MULT,
                    DIV,
                };

                OperatorTokenType(OPERATOR operator_t) : operator_t(operator_t) {}

                OPERATOR getOperatorTokenType() const { return operator_t; }
            private:
                OPERATOR operator_t;
            };
            bool operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op);


            struct ParamTokenType
            {
            public:
                enum class PARAM
                {
                    ROUND_OPEN,
                    ROUND_CLOSE,
                };

                ParamTokenType(PARAM param_t) : param_t(param_t) {}

                PARAM getParamTokenType() const { return param_t; }
            private:
                PARAM param_t;
            };
            bool operator==(const ParamTokenType& l_op, const ParamTokenType& r_op);


            struct IdentifierTokenType
            {
            public:
                IdentifierTokenType(const std::string& id) : id(id) {}
            
                std::string getIdentifier() const { return id; }
            private:
                std::string id;
            };
            bool operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op);


            struct TerminationTokenType
            {
            public:
                enum class TERMINATION
                {
                    END_OF_INPUT,
                    END_OF_LINE
                };
                TerminationTokenType(TERMINATION term_t) : term_t(term_t) {}

                TERMINATION getTerminationTokenType() const { return term_t; }
            private:
                TERMINATION term_t;
            };
            bool operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op);


            struct TokenType
            {
            public:
                enum class TOKEN
                {
                    OPERATOR,
                    PARAM,
                    NUM,
                    IDENTIFIER,
                    TERMINATION,
                };

                TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                TokenType(ParamTokenType&& param) : token_t(TOKEN::PARAM), token(std::move(param)) {}
                TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}
                TokenType(TerminationTokenType&& term) : token_t(TOKEN::TERMINATION), token(std::move(term)) {}

                TOKEN getTokenType() const { return token_t; }
                OperatorTokenType getOperatorToken() const { try{ return std::get<OperatorTokenType>(token); } catch(...) { throw std::runtime_error("getOperatorToken"); } }
                ParamTokenType getParamToken() const { try{ return std::get<ParamTokenType>(token); } catch(...) { throw std::runtime_error("getParamToken"); } }
                NumTokenType getNumToken() const { try{ return std::get<NumTokenType>(token); } catch(...) { throw std::runtime_error("getNumToken"); } }
                IdentifierTokenType getIdentifierToken() const { try{ return std::get<IdentifierTokenType>(token); } catch(...) { throw std::runtime_error("getIdentifierToken"); } }
                TerminationTokenType getTerminationToken() const { try{ return std::get<TerminationTokenType>(token); } catch(...) { throw std::runtime_error("getTerminationToken"); } }

            private:
                TOKEN token_t;
                std::variant<OperatorTokenType, ParamTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType> token;
            };
            bool operator==(const TokenType& l_op, const TokenType& r_op);

        } // namespace tok
    } // namespace calc
} // namespace alg
