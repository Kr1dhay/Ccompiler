#include "ast_switch_statement.hpp"


namespace ast{


    void SwitchStatement::EmitRISC(std::ostream &stream, Context &context) const{
        int switchRegister = context.allocateRegister(stream);
        expression_->EmitRISC(stream, context);
        stream << "mv x" << switchRegister << ", a0" << std::endl;

        std::string endSwitch = context.makeLabel("endSwitch");

        context.clearPendingNextCase();
        context.setSwitchRegister(switchRegister);
        context.setSwitchEnd(endSwitch);

        if (statement_) {
            statement_->EmitRISC(stream, context);
        }

        if (context.getPendingNextCase()) {
            stream << *context.getPendingNextCase() << ":" << std::endl;
            context.clearPendingNextCase();
        }

        stream << endSwitch << ":" << std::endl;

        context.popSwitchEnd();
        context.popSwitchRegister();
    }

    void SwitchStatement::Print(std::ostream &stream) const {
        stream << "switch (";
        expression_->Print(stream);
        stream << ") {" << std::endl;
        statement_->Print(stream);
        stream << "}" << std::endl;
    }
}
