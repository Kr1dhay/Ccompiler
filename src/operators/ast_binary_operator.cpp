#include "operators/ast_binary_operator.hpp"

namespace ast {

 BinaryOperator::BinaryOperator(BinOp op, NodePtr left, NodePtr right)
        : op_(std::move(op)), left_(std::move(left)), right_(std::move(right)) {}


void BinaryOperator::EmitRISC(std::ostream &stream, Context &context) const
{
    // Evaluate left and right subexpressions

    int leftReg = context.allocateRegister(stream);
    left_->EmitRISC(stream, context);
    stream << "mv x" << leftReg << ", a0" << std::endl;

    int rightReg = context.allocateRegister(stream);
    right_->EmitRISC(stream, context);
    stream << "mv x" << rightReg << ", a0" << std::endl;


    switch (op_) {
        case BinOp::Add:
            stream << "  add a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Sub:
            stream << "  sub a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Mul:
            stream << "  mul a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Div:
            stream << "  div a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        default:
            throw std::runtime_error("No valid binary operator");
            break;
    }

    context.freeRegister(leftReg);
    context.freeRegister(rightReg);

}

void BinaryOperator::Print(std::ostream &stream) const
{
    stream << "(";
    left_->Print(stream);
    stream << " ";

    switch (op_) {
        case BinOp::Add: stream << "+"; break;
        case BinOp::Sub: stream << "-"; break;
        case BinOp::Mul: stream << "*"; break;
        case BinOp::Div: stream << "/"; break;
    }

    stream << " ";
    right_->Print(stream);
    stream << ")";
}


}
