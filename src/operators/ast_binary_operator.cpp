#include "operators/ast_binary_operator.hpp"

// namespace ast {

// void BinaryOp::EmitRISC(std::ostream &stream, Context &context) const
// {
//     // Evaluate left and right subexpressions
//     left_->EmitRISC(stream, context);
//     stream << "  mv t0, a0\n";  // Save left result

//     right_->EmitRISC(stream, context);
//     stream << "  mv t1, a0\n";  // Save right result

//     if (op_ == "+")
//         stream << "  add a0, t0, t1\n";
//     else if (op_ == "-")
//         stream << "  sub a0, t0, t1\n";
//     else if (op_ == "*")
//         stream << "  mul a0, t0, t1\n";
//     else if (op_ == "/")
//         stream << "  div a0, t0, t1\n";
//     else
//         stream << "  # Unsupported binary operator\n";
// }

// void BinaryOp::Print(std::ostream &stream) const
// {
//     stream << "(";
//     left_->Print(stream);
//     stream << " " << op_ << " ";
//     right_->Print(stream);
//     stream << ")";
// }

// }
