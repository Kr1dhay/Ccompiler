#include "operators/ast_binary_operator.hpp"

namespace ast {


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
            stream << "mul a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Div:
            stream << "div a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Mod:
            stream << "rem a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Shr:
            stream << "sra a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Shl:
            stream << "sll a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Lt:
            stream << "slt a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::Gt:
            stream << "slt a0, x" << rightReg << ", x" << leftReg << std::endl;
            break;
        case BinOp::Leq:
                stream << "slt a0, x" << rightReg << ", x" << leftReg << std::endl;
                stream << "xori a0, a0, 1" << std::endl;
                break;
        case BinOp::Geq:
            stream << "slt a0, x" << leftReg << ", x" << rightReg << std::endl;
            stream << "xori a0, a0, 1" << std::endl;
            break;
        case BinOp::Eq:
            stream << "  xor  a0, x" << leftReg << ", x" << rightReg << std::endl;
            stream << "  sltiu a0, a0, 1" << std::endl;
            break;
        case BinOp::Neq:
            stream << "  xor  a0, x" << leftReg << ", x" << rightReg << std::endl;
            stream << "  sltiu a0, a0, a0" << std::endl;
            break;
        case BinOp::BitAnd:
            stream << "  and  a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::BitXor:
            stream << "  xor  a0, x" << leftReg << ", x" << rightReg << std::endl;
            break;
        case BinOp::BitOr:
            stream << "  or   a0, x" << leftReg << ", x" << rightReg << std::endl;
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
        case BinOp::Mod: stream << "%"; break;
        case BinOp::Lt: stream << "<"; break;
        case BinOp::Gt: stream << ">"; break;
        case BinOp::Leq: stream << "<="; break;
        case BinOp::Geq: stream << ">="; break;
        case BinOp::Shl: stream << "<<"; break;
        case BinOp::Shr: stream << ">>"; break;
        case BinOp::Eq: stream << "=="; break;
        case BinOp::Neq: stream << "!="; break;
        case BinOp::BitAnd: stream << "&"; break;
        case BinOp::BitXor: stream << "^"; break;
        case BinOp::BitOr: stream << "|"; break;
    }

    stream << " ";
    right_->Print(stream);
    stream << ")";
}

int BinaryOperator::getValue() const {
    int l = left_->getValue();
    int r = right_->getValue();
    switch (op_) {
        case BinOp::Add: return l + r;
        case BinOp::Sub: return l - r;
        case BinOp::Mul: return l * r;
        case BinOp::Div: return l / r;
        case BinOp::Mod: return l % r;
        case BinOp::Shl: return l << r;
        case BinOp::Shr: return l >> r;
        case BinOp::BitAnd: return l & r;
        case BinOp::BitOr: return l | r;
        case BinOp::BitXor: return l ^ r;
        case BinOp::Lt: return l < r;
        case BinOp::Gt: return l > r;
        case BinOp::Leq: return l <= r;
        case BinOp::Geq: return l >= r;
        case BinOp::Eq: return l == r;
        case BinOp::Neq: return l != r;
        default: throw std::runtime_error("unsupported op in const expr");
    }
}


}
