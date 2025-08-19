#pragma once

#include "ast_node.hpp"


namespace ast{

    class ArrayDeclarator : public Node{

        private:
        NodePtr direct_declarator_;
        NodePtr constant_expression_;

        public:

            ArrayDeclarator(NodePtr direct_declarator, NodePtr constant_expression)
        : direct_declarator_(std::move(direct_declarator)), constant_expression_(std::move(constant_expression)) {}

        virtual void EmitRISC(std::ostream& stream, Context& context) const override;
        virtual void Print(std::ostream& stream) const override;
        std::string getName() const override;

    };
}
