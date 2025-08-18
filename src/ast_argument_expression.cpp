
#include "ast_argument_expression.hpp"

namespace ast{

void ArgumentExpression::EmitRISC(std::ostream &stream, Context &context) const {
    int reg = context.storeArgument();

    expr_->EmitRISC(stream, context);

    if (reg == 10) {
        stream << "mv x28, a0" << std::endl;
    } else{
        stream << "mv x" << reg << ", " << "a0" << std::endl;
    }

}

void ArgumentExpression::Print(std::ostream &stream) const {
    stream << "ArgumentExpression: ";
    if (expr_) {
        expr_->Print(stream);
    } else {
        stream << "null";
    }
}

}
