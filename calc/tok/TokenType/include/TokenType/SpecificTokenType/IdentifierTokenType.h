#include "ITokenType.h"
#include <string_view>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class IdentifierTokenType : public ITokenType
            {
            public:
                constexpr explicit IdentifierTokenType(std::string_view identifier) noexcept;

                constexpr std::string_view getIdentifier() const;

            private:
                std::string_view identifier;
            };

            constexpr bool operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op);
        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;


constexpr IdentifierTokenType::IdentifierTokenType(std::string_view identifier) noexcept :
    identifier(identifier)
{}

constexpr std::string_view IdentifierTokenType::getIdentifier() const
{
    return identifier;
}

// non-member func
constexpr bool alg::calc::tok::operator==(const IdentifierTokenType& l_op, const IdentifierTokenType& r_op)
{
    return l_op.getIdentifier() == r_op.getIdentifier();
}
