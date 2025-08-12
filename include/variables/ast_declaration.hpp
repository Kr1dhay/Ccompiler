#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"



namespace ast {

class Declaration : public Node {
private:
    TypeSpecifier type_specifier_;
    NodePtr init_declarators_;

public:
    // Change constructor to take TypeSpecifier directly
    Declaration(TypeSpecifier type_spec, NodePtr declarators)
        : type_specifier_(type_spec), init_declarators_(std::move(declarators)) {}

    // Alternative constructor for empty declarator list
    Declaration(TypeSpecifier type_spec)
        : type_specifier_(type_spec), init_declarators_() {}

    virtual void EmitRISC(std::ostream& stream, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;

};


}
