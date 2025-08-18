#pragma once

#include "ast_node.hpp"


namespace ast{

class ArgumentExpression : public Node {
    private:
        NodePtr expr_;

public:
    ArgumentExpression(NodePtr expr) : expr_(std::move(expr)) {}

    void EmitRISC(std::ostream &stream, Context &context) const override;

    void Print(std::ostream &stream) const override;

};


}
