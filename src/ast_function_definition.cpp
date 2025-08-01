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
    stream << "addi sp, sp, -16" << std::endl;      // Allocate space for ra + fp
    stream << "sw ra, 12(sp)" << std::endl;         // Save return address
    stream << "sw s0, 8(sp)" << std::endl;          // Save old frame pointer (s0 is fp)
    stream << "addi s0, sp, 16" << std::endl;       // Set new frame pointer (fp = sp + 16)

    context.enterScope(); // Updates internal state


    std::string returnLabel = context.makeLabel("epilogue");
    context.setCurrentEndLabel(returnLabel);
    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context);
    }


    // === Epilogue ===
    context.exitScope(); // Optional: could eventually emit variable deallocations

    stream << returnLabel << ":" << std::endl;
    stream << "lw ra, 12(sp)" << std::endl;
    stream << "lw s0, 8(sp)" << std::endl;
    stream << "addi sp, sp, 16" << std::endl;
    stream << "jr ra" << std::endl;

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
