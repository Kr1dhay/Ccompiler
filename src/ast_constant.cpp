#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context&) const
{
    stream << "li a0, " << value_ << std::endl; // Load immediate value into a0
}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

int IntConstant::getValue() const {
    return value_;
}


} // namespace ast
