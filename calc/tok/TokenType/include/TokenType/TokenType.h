#pragma once
#include <optional>
#include <string_view>
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

                constexpr explicit NumTokenType(NUM num_t, std::string_view scalar) : num_t(num_t), scalar(scalar) {}

                NUM getNumTokenType() const { return num_t; }
                std::string_view getScalar() const { return scalar; }

            private:
                NUM num_t;
                std::string_view scalar;
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
            struct ParamTokenType
            {
            public:
                enum class PARAM
                {
                    ROUND_OPEN,
                    ROUND_CLOSE,
                };

                constexpr explicit ParamTokenType(PARAM param_t) : param_t(param_t) {}

                PARAM getParamTokenType() const { return param_t; }
            private:
                PARAM param_t;
            };
            struct IdentifierTokenType
            {
            public:
                constexpr explicit IdentifierTokenType(std::string_view id) : id(id) {}
            
                std::string_view getIdentifier() const { return id; }
            private:
                std::string_view id;
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
            bool operator==(const ParamTokenType& l_op, const ParamTokenType& r_op);
            bool operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op);
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

                constexpr explicit TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                constexpr explicit TokenType(ParamTokenType&& param) : token_t(TOKEN::PARAM), token(std::move(param)) {}
                constexpr explicit TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                constexpr explicit TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}
                constexpr explicit TokenType(TerminationTokenType&& term) : token_t(TOKEN::TERMINATION), token(std::move(term)) {}

                TOKEN getTokenType() const { return token_t; }
                
                OperatorTokenType getOperatorToken() const;
                ParamTokenType getParamToken() const;
                NumTokenType getNumToken() const;
                IdentifierTokenType getIdentifierToken() const;
                TerminationTokenType getTerminationToken() const;

            private:
                TOKEN token_t;
                std::variant<OperatorTokenType, ParamTokenType, NumTokenType, IdentifierTokenType, TerminationTokenType> token;
            };
            bool operator==(const TokenType& l_op, const TokenType& r_op);

        } // namespace tok
    } // namespace calc
} // namespace alg
