#ifndef SNAKE_H
#define SNAKE_H
#include <blockmap.h>
#include <queue>
#include <time.h>//用时间实现伪随即

class BlockMap;
class Snake
{
public:
    BlockMap * blockmap;
    int length = 1;
    std::shared_ptr<Node> head = NULL;
    std::shared_ptr<Node> tail = NULL;
    std::shared_ptr<Node> path = NULL; // 路径的头结点
public:
    Snake();
    Snake(int x,int y,int type);
    void setBlockMap(BlockMap * bm);

    bool nextStep();
    std::shared_ptr<Node> search();
    void visitReflush();
    void snakeReflush();
    void generateTarget();
    bool checkNodeAvailability(int, int);
    int getDirection(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);
    void reSearchPath();
    bool checkSnake(std::shared_ptr<Node> n);
};

#endif // SNAKE_H
