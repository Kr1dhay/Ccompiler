#include "ast/ast_root.hpp"

namespace ast {

void Root::EmitRISC(std::ostream& stream, Context& context) const
{
    // Emit top-level assembler directives
    stream << ".text" << std::endl;

    // Generate code for the translation unit
    if (translation_unit_ != nullptr) {
        translation_unit_->EmitRISC(stream, context);
    }
}

void Root::Print(std::ostream& stream) const
{
    if (translation_unit_ != nullptr) {
        translation_unit_->Print(stream);
    }
}

}
