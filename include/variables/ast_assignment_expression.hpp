#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"



namespace ast{

class AssignmentExpression : public Node
{
private:
    NodePtr left_;
    NodePtr op_;
    NodePtr right_;

public:

    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;


};

}
