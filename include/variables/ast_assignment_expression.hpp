#pragma once
#include "ast_node.hpp"
#include "ast_context.hpp"





enum class AssignmentOp {
  Assign
//   MulAssign, DivAssign, ModAssign, AddAssign, SubAssign,
//   ShlAssign, ShrAssign, AndAssign, XorAssign, OrAssign
};

namespace ast {

class AssignmentExpression : public Node {
private:
    NodePtr left_;                 // lvalue (Identifier for now)
    AssignmentOp op_;              // =, +=, etc.
    NodePtr right_;                // rvalue expression

public:
    AssignmentExpression(NodePtr left, AssignmentOp op, NodePtr right)
        : left_(std::move(left)), op_(op), right_(std::move(right)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
