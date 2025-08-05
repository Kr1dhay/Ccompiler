// InitDeclarator
// Role: represents one declared variable plus its optional initializer.

#include "variables/ast_init_declarator.hpp"


namespace ast {

    void InitDeclarator::EmitRISC(std::ostream &stream, Context &context) const {
        // Emit RISC code for the declarator
        declarator_->EmitRISC(stream, context);

        // If there is an initializer, emit code for it
        if (initialiser_) {
            initialiser_->EmitRISC(stream, context);
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
