#pragma once

#include "ast_node.hpp"


namespace ast{


class IfStatement : public Node {
private:
        NodePtr condition_;
        NodePtr then_branch_;

public:
    IfStatement(NodePtr condition, NodePtr then_branch)
        : condition_(std::move(condition)), then_branch_(std::move(then_branch)) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;

    void Print(std::ostream &stream) const override;

};

}
