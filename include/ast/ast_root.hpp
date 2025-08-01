#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"

namespace ast {

class Root : public Node {
public:
    Root(NodePtr translation_unit) : translation_unit_(std::move(translation_unit)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

private:
    NodePtr translation_unit_;
};

}
