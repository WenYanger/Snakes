#ifndef BLOCKMAP_H
#define BLOCKMAP_H
#include <stdio.h>
#include <node.h>
#include <snake.h>
#include <stdlib.h>//rand函数和srand函数
#include <time.h>//用时间实现伪随即
#include <queue>
#include <memory>

class Snake;
class BlockMap
{
public:
    Snake ** sa;
    int **blockMap;
    int **visit; //记录搜索过的点，减少广度搜索个数
    int width;
    int height;
    int snakeNum;
    std::shared_ptr<Node> target=NULL;
public:
    BlockMap();
    BlockMap(Snake ** sa,int ptrNum, int width, int height);

    bool autoReflush();
    void mapReflush();
    void snakeReflush();
    void visitReflush();
    void nextStep();
    std::shared_ptr<Node> search();
    void noticeAllSnakesForNewPath();

};

#endif // BLOCKMAP_H
