#include "ast_while_statement.hpp"

namespace ast{

void WhileStatement::EmitRISC(std::ostream &stream, Context &context) const {
    std::string start_label = context.makeLabel("while_start");
    std::string end_label = context.makeLabel("while_end");

    stream << start_label << ":" << std::endl;
    condition_->EmitRISC(stream, context);
    stream << "beq a0, x0, " << end_label << std::endl; // if condition is false, exit loop
    body_->EmitRISC(stream, context);
    stream << "j " << start_label << std::endl; // jump back to the start of the loop
    stream << end_label << ":" << std::endl; // end label for the loop

}


void WhileStatement::Print(std::ostream &stream) const {
    stream << "while (";
    condition_->Print(stream);
    stream << ") {";
    body_->Print(stream);
    stream << "}";
}

} // namespace ast
