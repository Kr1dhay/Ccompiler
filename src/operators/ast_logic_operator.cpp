#include "operators/ast_logic_operator.hpp"

namespace ast {


void LogicOperator::EmitRISC(std::ostream &stream, Context &context) const
{
    // Evaluate left and right subexpressions

    left_->EmitRISC(stream, context);

    std::string shortCircuit = context.makeLabel("shortCircuit");
    std::string logicEnd = context.makeLabel("logicEnd");

    switch (op_) {
        case LogicOp::LogicAnd:
            // If LHS == 0, short-circuit to false
            stream << "  beq  a0, x0, " << shortCircuit << std::endl;

            // Otherwise evaluate RHS and booleanize it
            right_->EmitRISC(stream, context);              // a0 = RHS value
            stream << "  sltu a0, x0, a0" << std::endl;  // a0 = (RHS != 0) ? 1 : 0
            stream << "  j " << logicEnd << std::endl;

            // Short-circuit false: LHS was 0 ⇒ result 0
            stream << shortCircuit << ":" << std::endl;
            stream << "  li   a0, 0" << std::endl;

            // End
            stream << logicEnd << ":" << std::endl;
            break;
        case LogicOp::LogicOr:
            stream << "  bne  a0, x0, " << shortCircuit << std::endl;

            // Otherwise evaluate RHS and booleanize it
            right_->EmitRISC(stream, context);              // a0 = RHS
            stream << "  sltu a0, x0, a0" << std::endl;     // a0 = (RHS != 0) ? 1 : 0
            stream << "  j " << logicEnd << std::endl;

            // Short-circuit true: LHS was nonzero ⇒ result 1
            stream << shortCircuit << ":" << std::endl;
            stream << "  li   a0, 1" << std::endl;

            // End
            stream << logicEnd << ":" << std::endl;
            break;
    }


}

void LogicOperator::Print(std::ostream &stream) const
{
    stream << "(";
    left_->Print(stream);
    stream << " ";
    switch (op_) {
        case LogicOp::LogicAnd: stream << "&&"; break;
        case LogicOp::LogicOr: stream << "||"; break;
    }
    right_->Print(stream);
    stream << ")";
}

}
