#pragma once

#include "ast_node.hpp"


namespace ast{


class IfElseStatement : public Node {
private:
        NodePtr condition_;
        NodePtr then_branch_;
        NodePtr else_branch_;

public:
    IfElseStatement(NodePtr condition, NodePtr then_branch, NodePtr else_branch)
        : condition_(std::move(condition)), then_branch_(std::move(then_branch)), else_branch_(std::move(else_branch)) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;

    void Print(std::ostream &stream) const override;

};

}
