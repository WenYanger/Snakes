#include "blockmap.h"

BlockMap::BlockMap()
{

}

BlockMap::BlockMap(Snake **sa, int ptrNum, int width, int height) : sa(sa),snakeNum(ptrNum),width(width),height(height)
{
    setlocale(LC_CTYPE, ""); // 配合wprintf使用，输出特殊符号

    int **newBlockMap = new int*[height];
    for(int i=0;i<height;i++){
        newBlockMap[i] = new int[width];
    }

    int **newVisit = new int*[height];
    for(int i=0;i<height;i++){
        newVisit[i] = new int[width];
    }

    //初始化地图
    /*
     * 0: Target
     * 1: Body
     * 2: HeadUp
     * 3: HeadRight
     * 4: HeadDown
     * 5: HeadLeft
     * 6: Free Block
     * 7: Banned Block
     */
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(i==0||j==0||i==height-1||j==width-1){
                newBlockMap[i][j] = 7;
            }
            else{
                newBlockMap[i][j] = 6;
            }
            newVisit[i][j] = 0;
        }
    }

    for(int i=0;i<ptrNum;i++){
        newBlockMap[sa[i]->head->x][sa[i]->head->y] = 4;sa[i]->head->type;
        newVisit[sa[i]->head->x][sa[i]->head->y] = 1;
    }

    this->blockMap = newBlockMap;
    this->visit = newVisit;
}


bool BlockMap::autoReflush()
{
    this->snakeReflush();
    this->mapReflush();
    return true;
}

void BlockMap::mapReflush()
{
    if(this->blockMap){
        int width = this->width;
        int height = this->height;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                switch (this->blockMap[i][j]) {
                case 0:
                    wprintf(L"⊙");
                    break;
                case 1:
                    wprintf(L"■");
                    break;
                case 2:
                    wprintf(L"↑");
                    break;
                case 3:
                    wprintf(L"→");
                    break;
                case 4:
                    wprintf(L"↓");
                    break;
                case 5:
                    wprintf(L"←");
                    break;
                case 6:
                    wprintf(L"□");
                    break;
                case 7:
                    wprintf(L"■");
                    break;
                default:
                    break;
                }
            }
            std::cout<<"\n";
        }
    }
}

//将snake信息刷入map中
void BlockMap::snakeReflush()
{
    //根据每条蛇的状态更新地图状态；
    for(int i=0;i<this->snakeNum;i++){
        std::shared_ptr<Node> cn = this->sa[i]->head; //cn=CurrentNode
        this->blockMap[cn->x][cn->y]=cn->type;
        while(cn=cn->nextnode){
            this->blockMap[cn->x][cn->y]=1;
        }
    }
}

void BlockMap::visitReflush()
{
    int height = this->height;
    int width = this->width;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            this->visit[i][j] = 0;
        }
    }
}

void BlockMap::noticeAllSnakesForNewPath()
{
    for(int i=0;i <this->snakeNum ; i++)
    {
        this->sa[i]->reSearchPath();
    }
}


