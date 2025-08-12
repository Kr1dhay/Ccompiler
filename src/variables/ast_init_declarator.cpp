// InitDeclarator
// Role: represents one declared variable plus its optional initializer.

#include "variables/ast_init_declarator.hpp"


namespace ast {

    void InitDeclarator::EmitRISC(std::ostream &stream, Context &context) const {
        // Emit RISC code for the declarator

        std::string varName = declarator_->getName();

        int offset = context.addLocalVar(varName, stream);

        initialiser_->EmitRISC(stream, context);


        stream << "sw a0, " << offset << "(fp)" << std::endl;

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
