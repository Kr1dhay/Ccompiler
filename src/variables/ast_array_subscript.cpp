#include "variables/ast_array_subscript.hpp"



namespace ast{

    void ArraySubscript::EmitRISC(std::ostream& stream, Context& context) const {
        // base is identifier
        int addr = context.allocateRegister(stream);
        EmitAddress(stream, context, addr);
        stream << "lw a0, 0(x" << addr << ")" << std::endl;
        context.freeRegister(addr);
    }

    void ArraySubscript::Print(std::ostream& stream) const {

        stream << "array" << std::endl;
    }

    std::string ArraySubscript::getName() const {
        return identifier_->getName();
    }

    void ArraySubscript::EmitAddress(std::ostream& s, Context& ctx, int destReg) const {
    const variable& var = ctx.getVariable(identifier_->getName());

    // index -> a0
    int idx = ctx.allocateRegister(s);
    expression_->EmitRISC(s, ctx);
    s << "mv x" << idx << ", a0\n";

    // scale by 4 (int)
    s << "slli x" << idx << ", x" << idx << ", 2\n";

    // base = s0 + var.offset
    int base = ctx.allocateRegister(s);
    s << "addi x" << base << ", s0, " << var.offset << "\n";

    // dest = base + scaled index
    s << "add x" << destReg << ", x" << base << ", x" << idx << "\n";

    ctx.freeRegister(base);
    ctx.freeRegister(idx);
}


}
