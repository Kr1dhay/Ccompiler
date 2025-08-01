#pragma once

#include "./ast_node.hpp"

namespace ast{

enum class BinOp {
    Add,
    Sub,
    Mul,
    Div
};

class BinaryOperator : public Node{
    private:
        BinOp op_;
        NodePtr left_;
        NodePtr right_;

    public:
        BinaryOperator(BinOp op_, NodePtr left, NodePtr right);

    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};

}
