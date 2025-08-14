#pragma once

#include "./ast_node.hpp"

namespace ast {


    enum class LogicOp {
    LogicAnd,
    LogicOr
};


class LogicOperator : public Node{
    private:
        LogicOp op_;
        NodePtr left_;
        NodePtr right_;

    public:

         LogicOperator(LogicOp op, NodePtr left, NodePtr right)
        : op_(op), left_(std::move(left)), right_(std::move(right)) {}


    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};
}
