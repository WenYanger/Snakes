#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <memory>


class Node
{
public:
    int x;
    int y;
    int type;

public:
    std::shared_ptr<Node> prenode;
    std::shared_ptr<Node> nextnode;

    Node();
    //~Node();
    Node(int x,int y);
    Node(int x,int y, int type);
    Node(int x,int y, std::shared_ptr<Node> prenode, std::shared_ptr<Node> nextnode);


    friend std::ostream& operator<< (std::ostream &os,std::shared_ptr<Node> nd)
    {
        os<<"X: "<<nd->x<<"\n"<<"Y: "<<nd->y<<"\n";
        return os;
    }

    bool operator== (Node* nd) const
    {
        if(this->x == nd->x && this->y == nd->y){
            return true;
        }
        else{
            return false;
        }
    }
};

#endif // NODE_H
