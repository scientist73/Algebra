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

                explicit NumTokenType(NUM num_t, std::string scalar) : num_t(num_t), scalar(scalar) {}

                NUM getNumTokenType() const { return num_t; }
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

                constexpr explicit OperatorTokenType(OPERATOR operator_t) : operator_t(operator_t) {}

                OPERATOR getOperatorTokenType() const { return operator_t; }
            private:
                OPERATOR operator_t;
            };
            struct ParenTokenType
            {
            public:
                enum class PAREN
                {
                    ROUND_OPEN,
                    ROUND_CLOSE,
                };

                constexpr explicit ParenTokenType(PAREN paren_t) : paren_t(paren_t) {}

                PAREN getParenTokenType() const { return paren_t; }
            private:
                PAREN paren_t;
            };
            struct IdentifierTokenType
            {
            public:
                explicit IdentifierTokenType(std::string id) : id(id) {}
            
                std::string getIdentifier() const { return id; }
            private:
                std::string id;
            };
            struct TerminationTokenType
            {
            public:
                enum class TERMINATION
                {
                    END_OF_INPUT,
                    END_OF_LINE
                };
                constexpr explicit TerminationTokenType(TERMINATION term_t) : term_t(term_t) {}

                TERMINATION getTerminationTokenType() const { return term_t; }
            private:
                TERMINATION term_t;
            };

            bool operator==(const NumTokenType& l_op, const NumTokenType& r_op);
            bool operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op);
            bool operator==(const ParenTokenType& l_op, const ParenTokenType& r_op);
            bool operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op);
            bool operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op);


            struct TokenType
            {
            public:
                enum class TOKEN
                {
                    OPERATOR,
                    PAREN,
                    NUM,
                    IDENTIFIER,
                    TERMINATION,
                };

                constexpr explicit TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                constexpr explicit TokenType(ParenTokenType&& paren) : token_t(TOKEN::PAREN), token(std::move(paren)) {}
                constexpr explicit TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                constexpr explicit TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}
                constexpr explicit TokenType(TerminationTokenType&& term) : token_t(TOKEN::TERMINATION), token(std::move(term)) {}

                TOKEN getTokenType() const { return token_t; }
                
                OperatorTokenType getOperatorToken() const;
                ParenTokenType getParenToken() const;
                NumTokenType getNumToken() const;
                IdentifierTokenType getIdentifierToken() const;
                TerminationTokenType getTerminationToken() const;

            private:
                TOKEN token_t;
                std::variant<OperatorTokenType, ParenTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType> token;
            };
            bool operator==(const TokenType& l_op, const TokenType& r_op);

        } // namespace tok
    } // namespace calc
} // namespace alg
