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
                enum class IDENTIFIER // change name and IDENTIFIER id as well
                {
                    FUNC,
                    CONST,
                    VAR,
                    UNKNOWN,
                };

                IdentifierTokenType(const std::string& name) : id(IDENTIFIER::UNKNOWN), name(name) {}
                IdentifierTokenType(IDENTIFIER id, const std::string& name) : id(id), name(name) {}
            
            private:
                IDENTIFIER id;
                std::string name;
            };


            struct TokenType
            {
            public:
                enum class TOKEN
                {
                    OPERATOR,
                    NUM,
                    IDENTIFIER,
                };

                TokenType(OperatorTokenType&& op) : token_t(TOKEN::OPERATOR), token(std::move(op)) {}
                TokenType(NumTokenType&& num) : token_t(TOKEN::NUM), token(std::move(num)) {}
                TokenType(IdentifierTokenType&& id) : token_t(TOKEN::IDENTIFIER), token(std::move(id)) {}

                TOKEN getTokenType() const { return token_t; }
                OperatorTokenType getOperatorToken() const { try{ return std::get<OperatorTokenType>(token); } catch(...) { throw std::runtime_error(""); } }
                NumTokenType getNumToken() const { try{ return std::get<NumTokenType>(token); } catch(...) { throw std::runtime_error(""); } }
                IdentifierTokenType getIdentifierToken() const { try{ return std::get<IdentifierTokenType>(token); } catch(...) { throw std::runtime_error(""); } }

            private:
                TOKEN token_t;
                std::variant<OperatorTokenType, NumTokenType, IdentifierTokenType> token;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
