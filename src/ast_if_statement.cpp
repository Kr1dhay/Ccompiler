#include "ast_if_statement.hpp"

namespace ast{

void IfStatement::EmitRISC(std::ostream &stream, Context &context) const {

    std::string true_label = context.makeLabel("if_true");
    std::string false_label = context.makeLabel("if_false");
    condition_->EmitRISC(stream, context);

    stream << "bne a0, x0, " << true_label << std::endl;
    stream << "j " << false_label << std::endl;
    stream << true_label << ":" << std::endl;
    then_branch_->EmitRISC(stream, context);
    stream << false_label << ":" << std::endl;

}


void IfStatement::Print(std::ostream &stream) const {
    stream << "if ";
    condition_->Print(stream);
    stream << " then ";
    then_branch_->Print(stream);
    stream << std::endl;
}

}
