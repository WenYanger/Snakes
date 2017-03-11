#ifndef BLOCKMAP_H
#define BLOCKMAP_H
#include <stdio.h>
#include <node.h>
#include <stdlib.h>//rand函数和srand函数
#include <time.h>//用时间实现伪随即
#include <queue>
#include <memory>

class blockmap
{
private:
    int width;
    int height;
    int **blockMap;
    int **visit; //记录搜索过的点，减少广度搜索个数
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> target=NULL;
    std::shared_ptr<Node> path=NULL; // 路径的头结点
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
    std::shared_ptr<Node> search();
    bool checkNodeAvailability(int, int);
    void generateTarget();
    int getDirection(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);


};

#endif // BLOCKMAP_H
