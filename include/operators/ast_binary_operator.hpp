#pragma once

#include "./ast_node.hpp"

namespace ast{

class BinaryOp : public Node{
    private:
        std::string op_;
        NodePtr left_;
        NodePtr right_;

    public:
        BinaryOp(std::string op, NodePtr left, NodePtr right)
        : op_(std::move(op)), left_(std::move(left)), right_(std::move(right)) {}

    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};

}
