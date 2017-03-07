#include "node.h"

Node::Node()
{

}

Node::Node(int x, int y):x(x),y(y),type(6),nextnode(nullptr),prenode(nullptr)
{}

Node::Node(int x,int y,int type):x(x),y(y),type(type),nextnode(nullptr),prenode(nullptr)
{}

Node::Node(int x, int y, Node* prenode, Node* nextnode):x(x),y(y),type(6),nextnode(nextnode),prenode(prenode)
{}

