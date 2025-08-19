#include "ast_case_statement.hpp"


namespace ast{


    void CaseStatement::EmitRISC(std::ostream &stream, Context &context) const{
        // Emit code for the constant expression

        if (context.getPendingNextCase()) {
            stream << *context.getPendingNextCase() << ":" << std::endl;
            context.clearPendingNextCase();
        }



        constant_expression_->EmitRISC(stream, context);

        // Generate a label for the next case
        std::string nextCaseLabel = context.makeLabel("nextCase");
        context.setPendingNextCase(nextCaseLabel);

        stream << "bne a0, x" << context.getSwitchRegister() << ", " << nextCaseLabel << std::endl;


        // Emit the statement for this case
        statement_->EmitRISC(stream, context);


    }

    void DefaultCaseStatement::EmitRISC(std::ostream &stream, Context &context) const{
        // Emit the default case label

        if (context.getPendingNextCase()) {
            stream << *context.getPendingNextCase() << ":" << std::endl;
            context.clearPendingNextCase();
        }

        stream << context.makeLabel("defaultCase") << ":" << std::endl;

        // Emit the statement for the default case
        statement_->EmitRISC(stream, context);
    }


    void CaseStatement::Print(std::ostream &stream) const {
        stream << "case ";
        constant_expression_->Print(stream);
        stream << ":" << std::endl;
        statement_->Print(stream);
    }

    void DefaultCaseStatement::Print(std::ostream &stream) const {
            stream << "case: " << std::endl;
            statement_->Print(stream);
    }
}
