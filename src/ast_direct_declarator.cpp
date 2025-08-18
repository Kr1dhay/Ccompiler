#include "ast_direct_declarator.hpp"

namespace ast {



void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    // identifier_->EmitRISC(stream, context);

    if (parameter_list_) {
        parameter_list_->EmitRISC(stream, context);
    }

}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
}

std::string DirectDeclarator::getName() const
{
    return identifier_->getName();
}


} // namespace ast
