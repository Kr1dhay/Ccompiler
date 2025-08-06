#include "variables/ast_declaration.hpp"


namespace ast {
    void Declaration::EmitRISC(std::ostream& stream, Context& context) const {
        // Set the current variable size based on the type
        context.setCurrentVariableSize(type);

        // Emit RISC code for each init declarator
        for (const auto& initDeclarator : initDeclarators) {
            initDeclarator->EmitRISC(stream, context);
        }

        context.setCurrentVariableSize(TypeSpecifier::INT); // Reset to default after declaration
    }

    void Declaration::Print(std::ostream& stream) const {
        stream << "Declaration(" << type << ", [";
        for (size_t i = 0; i < initDeclarators.size(); ++i) {
            initDeclarators[i]->Print(stream);
            if (i < initDeclarators.size() - 1) {
                stream << ", ";
            }
        }
        stream << "])";
    }
} // namespace ast
