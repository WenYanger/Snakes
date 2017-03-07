#ifndef BLOCKMAP_H
#define BLOCKMAP_H
#include <stdio.h>
#include <snake.h>
#include <node.h>
#include <stdlib.h>//rand函数和srand函数
#include <time.h>//用时间实现伪随即
#include <queue>

class blockmap
{
private:
    int width;
    int height;
    int **blockMap;
    int **visit; //记录搜索过的点，减少广度搜索个数
    Node *head;
    Node *target=NULL;
public:
    blockmap();
    blockmap(int width,int height);
    bool autoReflush();
    void travelsal();
private:

    void mapReflush();
    void snakeReflush();
    void visitReflush();
    void nextStep();
    Node* search();
    bool checkNodeAvailability(int, int);
    void generateTarget();




};

#endif // BLOCKMAP_H
