// InitDeclarator
// Role: represents one declared variable plus its optional initializer.

#include "variables/ast_init_declarator.hpp"


namespace ast {

    void InitDeclarator::EmitRISC(std::ostream &stream, Context &context) const {
        // Emit RISC code for the declarator

        std::string varName = declarator_->getName();
        int offset = context.addLocalVar(varName, stream);

        if (initialiser_) {
            initialiser_->EmitRISC(stream, context);
            const variable& var = context.getVariable(varName);
            if (var.reg != -1) {
                // Store directly in its register
                stream << "mv x" << var.reg << ", a0" << std::endl;
            } else {
                // Store into memory
                stream << "sw a0, " << offset << "(s0)" << std::endl;
            }
        }




    }



    void InitDeclarator::Print(std::ostream &stream) const {
        stream << "InitDeclarator(";
        if (declarator_) {
            declarator_->Print(stream);
        }
        if (initialiser_) {
            stream << ", ";
            initialiser_->Print(stream);
        }
        stream << ")";
    }

} // namespace ast
