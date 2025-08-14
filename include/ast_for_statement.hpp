#pragma once

#include "ast_node.hpp"

namespace ast {

class ForStatement : public Node {
private:
    NodePtr init_;
    NodePtr condition_;
    NodePtr increment_;
    NodePtr body_;

public:
    ForStatement(NodePtr init, NodePtr condition, NodePtr increment, NodePtr body)
        : init_(std::move(init)), condition_(std::move(condition)), increment_(std::move(increment)), body_(std::move(body)) {}

    ForStatement(NodePtr init, NodePtr condition, NodePtr body)
        : init_(std::move(init)), condition_(std::move(condition)), increment_(nullptr), body_(std::move(body)) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;
    void Print(std::ostream &stream) const override;
};

} // namespace ast
