#include "ast_node.hpp"

namespace ast {


std::string Node::getName() const
{
    std::cerr << "Tried to getSize of expression of something not implemented" << std::endl;
    return "Error: getName not implemented for this Node type";
}



void NodeList::PushBack(NodePtr item)
{
    nodes_.push_back(std::move(item));
}

void NodeList::EmitRISC(std::ostream& stream, Context& context) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context);
    }
}

void NodeList::Print(std::ostream& stream) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}

int NodeList::getSize() const
{
    return nodes_.size();
}

} // namespace ast
