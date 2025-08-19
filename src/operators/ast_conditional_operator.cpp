#include "operators/ast_conditional_operator.hpp"

namespace ast{

void ConditionalOperator::EmitRISC(std::ostream& stream, Context &context) const{
    condition_->EmitRISC(stream, context);

    std::string L_false = context.makeLabel("cond_false");
    std::string L_end   = context.makeLabel("cond_end");


    stream << "beq a0, x0, " << L_false << std::endl;

    trueExpr_->EmitRISC(stream, context);

    stream << "j " << L_end << std::endl;
    stream << L_false << ":" << std::endl;

    falseExpr_->EmitRISC(stream, context);

    stream << L_end << ":" << std::endl;

}


void ConditionalOperator::Print(std::ostream& stream) const{
    stream << "(";
    condition_->Print(stream);
    stream << " ? ";
    trueExpr_->Print(stream);
    stream << " : ";
    falseExpr_->Print(stream);
    stream << ")";
}
}
