// InitDeclarator
// Role: represents one declared variable plus its optional initializer.

#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"

namespace ast {
    class InitDeclarator : public Node{
    private:
        NodePtr declarator_;
        NodePtr initialiser_;

    public:

        InitDeclarator(NodePtr declarator, NodePtr initialiser)
            : declarator_(std::move(declarator)), initializer_(std::move(initialiser)) {}

        virtual void EmitRISC(std::ostream &stream, Context &context) const override;
        virtual void Print(std::ostream &stream) const override;





    }
}
