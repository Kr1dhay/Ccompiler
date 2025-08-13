#include "operators/ast_logic_operator.hpp"

namespace ast {


void LogicOperator::EmitRISC(std::ostream &stream, Context &context) const
{
    // Evaluate left and right subexpressions

    int leftReg = context.allocateRegister(stream);
    left_->EmitRISC(stream, context);
    stream << "mv x" << leftReg << ", a0" << std::endl;



    switch (op_) {
        case LogicOp::LogicAnd:
        stream << "  and  a0, x" << leftReg << ", x" << rightReg << std::endl;
        break;
        case LogicOp::LogicOr:
        stream << "  or   a0, x" << leftReg << ", x" << rightReg << std::endl;
        break;
    }

    int rightReg = context.allocateRegister(stream);
    right_->EmitRISC(stream, context);
    stream << "mv x" << rightReg << ", a0" << std::endl;

    context.freeRegister(leftReg);
    context.freeRegister(rightReg);

}

void LogicOperator::Print(std::ostream &stream) const
{
    // stream << "(";
    // left_->Print(stream);
    // stream << " ";

    // switch (op_) {
    //     case LogicOp::LogicAnd: stream << "&&"; break;
    //     case LogicOp::LogicOr: stream << "||"; break;
    // }

    // stream << " ";
    // right_->Print(stream);
    // stream << ")";
}


}
