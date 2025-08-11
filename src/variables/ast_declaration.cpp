#include "variables/ast_declaration.hpp"


namespace ast {
    void Declaration::EmitRISC(std::ostream& stream, Context& context) const {
        // Set the current variable size based on the type
        context.setCurrentVariableSize(type_specifier_);

        if (init_declarators_) {
            init_declarators_->EmitRISC(stream, context);
        }

        context.setCurrentVariableSize(TypeSpecifier::INT); // Reset to default after declaration
    }

    void Declaration::Print(std::ostream& stream) const {
        stream << "Declaration(" << type_specifier_ << ", [";
        init_declarators_->Print(stream);
        stream << "])";
    }
} // namespace ast
