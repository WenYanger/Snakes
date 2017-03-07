#ifndef SNAKE_H
#define SNAKE_H
#include <node.h>
#include <iostream>

class Snake
{
public:
    Node* headnode;

public:
    Snake();
    Snake(Node* headnode);
    void travelsal();
};

#endif // SNAKE_H
