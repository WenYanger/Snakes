#ifndef MAP_H
#define MAP_H
#include <snake.h>
#include <node.h>


class map
{
private:
    int width;
    int height;
    int **blockMap;
    Snake *snake;
public:
    map();
    map(int width,int height,int** nodeType);
    void autoReflush();
    void travelsal();
};

#endif // MAP_H
