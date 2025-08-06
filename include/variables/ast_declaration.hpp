#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"



namespace ast {

class Declaration : public Node {
private:
    TypeSpecifier type;                     // e.g., INT, FLOAT, etc.
    std::vector<NodePtr> initDeclarators;   // Each is an InitDeclarator

public:
    Declaration(TypeSpecifier t, std::vector<NodePtr>&& decls)
        : type(t), initDeclarators(std::move(decls)) {}

    virtual void EmitRISC(std::ostream& stream, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;

};


}
