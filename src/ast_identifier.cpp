#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{
    int offset = context.getVariableOffset(identifier_);
    stream << "lw a0, " << offset << "(fp)" << std::endl;
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
