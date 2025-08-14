#include "ast_for_statement.hpp"


namespace ast{

    void ForStatement::EmitRISC(std::ostream &stream, Context &context) const {


        std::string continueFor = context.makeLabel("continueFor");
        std::string endFor = context.makeLabel("endFor");

        init_->EmitRISC(stream, context);


        stream << continueFor <<  ":" << std::endl;
        condition_->EmitRISC(stream, context);

        stream << "beq a0, x0, " << endFor << std::endl;

        if (body_) {
            body_->EmitRISC(stream, context);
        }

        if (increment_) {
            increment_->EmitRISC(stream, context);
        }

        stream << "j " << continueFor << std::endl;
        stream << endFor <<  ":" << std::endl;
    }


    void ForStatement::Print(std::ostream &stream) const {
        stream << "for (";
        if (init_) {
            init_->Print(stream);
        }
        stream << "; ";
        if (condition_) {
            condition_->Print(stream);
        }
        stream << "; ";
        if (increment_) {
            increment_->Print(stream);
        }
        stream << ") ";
        if (body_) {
            body_->Print(stream);
        }
    }
}
