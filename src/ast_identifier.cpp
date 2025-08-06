#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context&) const
{
    stream << identifier_ << std::endl; // Emit the identifier as a RISC instruction
    // This is a placeholder; actual implementation may vary based on context
}

void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;
};


std::string Identifier::getName() const
{
    return identifier_;
}

} // namespace ast
