#include "ast_direct_declarator.hpp"

namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    stream << ".globl ";
    identifier_->EmitRISC(stream, context);
    stream << std::endl;


    identifier_->EmitRISC(stream, context);
    stream << ":" << std::endl;
}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
}

} // namespace ast
