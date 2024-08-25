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

                NUM getNumToken() const { return num_t; }
                std::string getScalar() const { return scalar; }

            private:
                NUM num_t;
                std::string scalar;
            };

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

            private:
                OPERATOR operator_t;
            };

            struct IdentifierTokenType
            {
            public:
                IdentifierTokenType(const std::string& name) : name(name) {}
            
            private:
                std::string name;
            };

            struct TerminationTokenType
            {
            public:
                enum class TERMINATION
                {
                    END_OF_INPUT,
                    END_OF_LINE
                };
                TerminationTokenType(TERMINATION term) : term(term) {}
            private:
                TERMINATION term;
            };


            struct TokenType
            {
            public:
                enum class TOKEN
                {
                    OPERATOR,
                    NUM,
                    IDENTIFIER,
                    TERMINATION,
                };

                TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}
                TokenType(TerminationTokenType&& term) : token_t(TOKEN::TERMINATION), token(std::move(term)) {}

                TOKEN getTokenType() const { return token_t; }
                OperatorTokenType getOperatorToken() const { try{ return std::get<OperatorTokenType>(token); } catch(...) { throw std::runtime_error(""); } }
                NumTokenType getNumToken() const { try{ return std::get<NumTokenType>(token); } catch(...) { throw std::runtime_error(""); } }
                IdentifierTokenType getIdentifierToken() const { try{ return std::get<IdentifierTokenType>(token); } catch(...) { throw std::runtime_error(""); } }
                TerminationTokenType getTerminationToken() const { try{ return std::get<TerminationTokenType>(token); } catch(...) { throw std::runtime_error(""); } }

            private:
                TOKEN token_t;
                std::variant<OperatorTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType> token;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
