#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    const variable& var = context.getVariable(identifier_);
    if (var.reg != -1) {
        stream << "mv a0, x" << var.reg << std::endl;
    } else {
        stream << "lw a0, " << var.offset << "(fp)" << std::endl;
    }
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
