#pragma once

#include "ast_node.hpp"


namespace ast{


    class ArraySubscript : public Node {

        private:
        NodePtr identifier_;
        NodePtr expression_;

        public:

            ArraySubscript(NodePtr identifier, NodePtr expression) : identifier_(std::move(identifier)), expression_(std::move(expression)) {}

            void EmitRISC(std::ostream &stream, Context &context) const override;
            void Print(std::ostream &stream) const override;

             std::string getName() const override;

            void EmitAddress(std::ostream& stream, Context& context, int destReg) const override;


    };
}
