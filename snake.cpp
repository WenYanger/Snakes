#include "snake.h"

Snake::Snake()
{

}

Snake::Snake(Node *headnode):headnode(headnode)
{}

void Snake::travelsal()
{
    if(this->headnode){
        Node* currentNode = this->headnode;
        do{
            std::cout<<currentNode;
        }while(currentNode = currentNode->nextnode);
    }
    else{
        std::cout<<"This Snack Dosen't have a HeadNode";
    }
}




