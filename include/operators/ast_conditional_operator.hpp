#pragma once

#include "ast_node.hpp"


namespace ast{

    class ConditionalOperator : public Node{
        private:
            NodePtr condition_;
            NodePtr trueExpr_;
            NodePtr falseExpr_;
        public:
            ConditionalOperator(NodePtr condition, NodePtr trueExpr, NodePtr falseExpr)
                : condition_(std::move(condition)), trueExpr_(std::move(trueExpr)), falseExpr_(std::move(falseExpr)) {}

            void EmitRISC(std::ostream& stream, Context &context) const override;

            void Print(std::ostream& stream) const override;
    };
}
