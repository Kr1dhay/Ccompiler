#pragma once

#include "ast_node.hpp"




namespace ast{

    class FunctionCall : public Node {
        private:
        NodePtr function_;
        NodePtr arguments_;

        public:
            FunctionCall(NodePtr function, NodePtr arguments)
                : function_(std::move(function)), arguments_(std::move(arguments)) {}

            void EmitRISC(std::ostream &stream, Context &context) const override;
            void Print(std::ostream &stream) const override;
    };
}
