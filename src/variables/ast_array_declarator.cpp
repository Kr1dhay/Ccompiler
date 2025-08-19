#include "variables/ast_array_declarator.hpp"



namespace ast{

    void ArrayDeclarator::EmitRISC(std::ostream& stream, Context& context) const {
        std::string array_name = direct_declarator_->getName();
        int len = constant_expression_->getValue();
        context.addLocalArray(array_name, len, stream);
    }

    void ArrayDeclarator::Print(std::ostream& stream) const {

        stream << "array" << std::endl;
    }

    std::string ArrayDeclarator::getName() const {
        return direct_declarator_->getName();
    }

}
