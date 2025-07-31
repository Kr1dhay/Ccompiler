#include "operators/ast_binary_operator.hpp"

namespace ast {

 BinaryOperator::BinaryOperator(BinOp op, NodePtr left, NodePtr right)
        : op_(std::move(op)), left_(std::move(left)), right_(std::move(right)) {}


void BinaryOperator::EmitRISC(std::ostream &stream, Context &context) const
{
    // Evaluate left and right subexpressions
    left_->EmitRISC(stream, context);
    stream << "  mv t0, a0" << std::endl;  // Save left result

    right_->EmitRISC(stream, context);
    stream << "  mv t1, a0" << std::endl;  // Save right result

    switch (op_) {
        case BinOp::Add:
            stream << "  add a0, t0, t1\n";
            break;
        case BinOp::Sub:
            stream << "  sub a0, t0, t1\n";
            break;
        case BinOp::Mul:
            stream << "  mul a0, t0, t1\n";
            break;
        case BinOp::Div:
            stream << "  div a0, t0, t1\n";
            break;
        default:
            stream << "  # Unsupported binary operator\n";
            break;
    }
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
