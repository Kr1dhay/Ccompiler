#include "ast_return_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, Context& context) const
{

    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context);
    }
    stream << "j " << context.getCurrentEndLabel() << std::endl;

}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
