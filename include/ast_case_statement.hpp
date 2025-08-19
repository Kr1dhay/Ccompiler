#pragma once

#include "ast_node.hpp"


namespace ast{

    class CaseStatement : public Node{
        private:
        NodePtr constant_expression_;
        NodePtr statement_;

        public:

        CaseStatement(NodePtr constant_expression, NodePtr statement)
            : constant_expression_(std::move(constant_expression)), statement_(std::move(statement)) {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;
    };


    class DefaultCaseStatement : public Node{
        private:
        NodePtr statement_;

        public:

        DefaultCaseStatement(NodePtr statement)
            : statement_(std::move(statement)) {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;
    };
}
