#include "variables/ast_assignment_expression.hpp"

using namespace ast;



void AssignmentExpression::EmitRISC(std::ostream& s, Context& context) const {

    std::string varName = left_->getName();
    const variable& var = context.getVariable(varName);

    switch (op_) {
        case AssignmentOp::Assign: {
            right_->EmitRISC(s, context);               // a0 = rhs
        }
    }

    if (var.length == 1) {
        if (var.reg != -1) {
            s << "mv x" << var.reg << ", a0" << std::endl;
        } else {
            s << "sw a0, " << var.offset << "(s0)" << std::endl;
        }
    } else{
        int regIdx = context.allocateRegister(s);
        left_->EmitAddress(s, context, regIdx);

        s << "sw a0, 0(x" << regIdx << ")" << std::endl; // store value in array
        context.freeRegister(regIdx);
    }

}

void AssignmentExpression::Print(std::ostream& s) const {
    s << "(assign ";
    left_->Print(s);
    s << " ";
    // optional: print op_
    right_->Print(s);
    s << ")";
}
