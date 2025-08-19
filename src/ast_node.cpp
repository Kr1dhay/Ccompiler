#include "ast_node.hpp"

namespace ast {


std::string Node::getName() const
{
    std::cerr << "Tried to getSize of expression of something not implemented" << std::endl;
    return "Error: getName not implemented for this Node type";
}

int Node::getValue() const
{
    std::cerr << "Tried to getValue of expression of something not implemented" << std::endl;
    return -1;
}


void Node::EmitAddress(std::ostream& stream, Context& context, int destReg) const{
    std::cerr << "Tried to EmitAddress of something not implemented" << std::endl;
    stream << "error" << std::endl;
    context.freeRegister(destReg);
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
