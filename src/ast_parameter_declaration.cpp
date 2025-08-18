#include "ast_parameter_declaration.hpp"


namespace ast{

    void ParameterDeclaration::EmitRISC(std::ostream& stream, Context& context) const {
        context.setCurrentVariableSize(declaration_specifiers_);

        std::string paramName = declarator_->getName();

        context.addLocalVarParam(paramName, stream);

    }

    void ParameterDeclaration::Print(std::ostream& stream) const {
        stream << declaration_specifiers_ << " ";
        if (declarator_) {
            declarator_->Print(stream);
        }
    }

}
