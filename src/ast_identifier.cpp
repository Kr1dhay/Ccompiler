#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    const variable& var = context.getVariable(identifier_);
    if (var.reg != -1) {
        stream << "mv a0, x" << var.reg << std::endl;
    } else {
        stream << "lw a0, " << var.offset << "(s0)" << std::endl;
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

void Identifier::EmitAddress(std::ostream& stream, Context& context, int destReg) const {

        const variable& var = context.getVariable(identifier_);
        stream << "addi x" << destReg << ", s0, " << var.offset << std::endl;
    }

} // namespace ast
