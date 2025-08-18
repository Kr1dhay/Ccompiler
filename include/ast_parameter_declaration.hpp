
#pragma once

#include "ast_node.hpp"

namespace ast{

class ParameterDeclaration : public Node {

private:
    TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;

public:
    ParameterDeclaration(TypeSpecifier declaration_specifiers, NodePtr declarator)
        : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)) {}

    ParameterDeclaration(TypeSpecifier declaration_specifiers)
        : declaration_specifiers_(declaration_specifiers), declarator_(nullptr) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

}
