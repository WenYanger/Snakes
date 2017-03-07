#ifndef NODE_H
#define NODE_H
#include <iostream>


class Node
{
public:
    int x;
    int y;
    int type;

public:
    Node* prenode;
    Node* nextnode;

    Node();
    Node(int x,int y);
    Node(int x,int y, int type);
    Node(int x,int y, Node *prenode, Node* nextnode);


    friend std::ostream& operator<< (std::ostream &os,Node *nd)
    {
        os<<"X: "<<nd->x<<"\n"<<"Y: "<<nd->y<<"\n";
        return os;
    }
};

#endif // NODE_H
