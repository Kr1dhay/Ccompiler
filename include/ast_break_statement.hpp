#pragma once

#include "ast_node.hpp"


namespace ast{

    class BreakStatement : public Node{

        public:
        BreakStatement() {}

        void EmitRISC(std::ostream &stream, Context &context) const override;
        void Print(std::ostream &stream) const override;
    };
}
