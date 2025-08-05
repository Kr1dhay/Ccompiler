#include "ast_function_definition.hpp"

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, Context& context) const
{
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.
    // stream << ".text" << std::endl;
    // stream << ".globl f" << std::endl;

    declarator_->EmitRISC(stream, context);

    // === Prologue ===
    stream << "addi sp, sp, -8" << std::endl;      // 4 for ra + 4 for s0
    stream << "sw ra, 4(sp)" << std::endl;         // ra saved at sp + 4
    stream << "sw s0, 0(sp)" << std::endl;         // s0 saved at sp + 0
    stream << "addi s0, sp, 8" << std::endl;       // fp = original sp


    context.enterScope(); // Updates internal state


    std::string returnLabel = context.makeLabel("epilogue");
    context.setCurrentEndLabel(returnLabel);
    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context);
    }


    // === Epilogue ===

    // int dynamicSize = -context.getCurrentFrameOffset();  // Total size used for locals
    // int totalFrameSize = 8 + dynamicSize;
    int totalFrameSize = 8; // 4 for ra + 4 for s0, no locals in this example

    stream << returnLabel << ":" << std::endl;
    stream << "lw ra, 4(sp)" << std::endl;
    stream << "lw s0, 0(sp)" << std::endl;
    stream << "addi sp, sp, " << totalFrameSize << std::endl;
    stream << "jr ra" << std::endl;

    context.exitScope();  // Now it's safe to pop the frame

}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
