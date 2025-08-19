#include "ast_break_statement.hpp"


namespace ast{


    void BreakStatement::EmitRISC(std::ostream &stream, Context &context) const{
        // Emit code for the constant expression
       std::string breakLabel = context.getSwitchEnd();

        if (breakLabel.empty()) {
            throw std::runtime_error("No active switch statement to break from.");
        }

        // Emit the jump to the end of the switch
        stream << "j " << breakLabel << std::endl;

    }

void BreakStatement::Print(std::ostream &stream) const{


    stream << "break" << std::endl;
}

}
