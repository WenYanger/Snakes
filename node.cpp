#include "node.h"

Node::Node()
{

}

Node::Node(int x, int y)
    :x(x),y(y),type(6),nextnode(nullptr),prenode(nullptr)
{}

Node::Node(int x,int y,int type)
    :x(x),y(y),type(type),nextnode(nullptr),prenode(nullptr)
{}

Node::Node(int x, int y, std::shared_ptr<Node> prenode, std::shared_ptr<Node> nextnode)
    :x(x),y(y),type(6),nextnode(nextnode),prenode(prenode)
{}

//Node::~Node()
//{
//    static int countNode = 0;
//    countNode++;
//    std::cout<<"countNode:"<<countNode<<std::endl;
//    //std::cout << "delete node" << std::endl;
//}

void Node::setType(int type){
    this->type = type;
}

