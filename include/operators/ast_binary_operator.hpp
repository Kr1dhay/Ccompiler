#pragma once

#include "./ast_node.hpp"

namespace ast{

enum class BinOp {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Shl,
    Shr,
    Lt,
    Gt,
    Leq,
    Geq,
    Eq,
    Neq,
    BitAnd,
    BitXor,
    BitOr,
};

class BinaryOperator : public Node{
    private:
        BinOp op_;
        NodePtr left_;
        NodePtr right_;

    public:

         BinaryOperator(BinOp op, NodePtr left, NodePtr right)
        : op_(op), left_(std::move(left)), right_(std::move(right)) {}


    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
    int getValue() const override;
};

}
