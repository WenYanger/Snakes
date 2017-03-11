#include "blockmap.h"

blockmap::blockmap()
{}

blockmap::blockmap(int width,int height):width(width),height(height)
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
    this->head = std::shared_ptr<Node>(new Node(1,1,4));
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

    this->blockMap = newBlockMap;
    this->visit = newVisit;
}

bool blockmap::autoReflush()
{
    this->nextStep();
    this->snakeReflush();
    this->mapReflush();

    return true;
}

void blockmap::mapReflush()
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
void blockmap::snakeReflush()
{
    std::shared_ptr<Node> cn = this->head; //cn=CurrentNode
    this->blockMap[cn->x][cn->y]=cn->type;
    while(cn=cn->nextnode){
        this->blockMap[cn->x][cn->y]=1;
    }
}

void blockmap::visitReflush()
{
    int height = this->height;
    int width = this->width;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            this->visit[i][j] = 0;
        }
    }
}

//使用广度优先搜索进行查找
void blockmap::nextStep()
{
    //1. 判断是否还有target,没有则给定新的target
    if(!this->target){
        this->generateTarget();
        //this->target = std::shared_ptr<Node>(new Node(5,5,0));
        //this->blockMap[5][5]=0;
    }
    std::cout<<this->target;
    std::cout<<this->head;

    //2. 使用算法改变snake状态
    if(!this->path){
        this->path = this->search();
        this->visitReflush();
    }
    //沿着path前进一格
    std::shared_ptr<Node> nextNode = this->path;
    this->path = this->path->prenode;
    if(nextNode->x == this->target->x && nextNode->y == this->target->y){
        //TODO: 处理头部方向问题
        int direction = this->getDirection(nextNode,this->head);
        this->head->setType(1);
        nextNode->setType(direction);
        this->head = nextNode;


        //TODO: 删除target
        this->target = nullptr;

    }
    else{
        int direction = this->getDirection(nextNode,this->head);
        this->head->setType(1);
        nextNode->nextnode = this->head;
        this->head->prenode = nextNode;
        this->head = nextNode;
        this->head->setType(direction);
//        nextNode->setType(4);
//        nextNode->nextnode = this->head;
//        this->head->prenode = nextNode;
//        this->head = nextNode;
        //1.删除蛇的尾结点
        std::shared_ptr<Node> tailNode = this->head->nextnode;
        while(tailNode){
            if(!tailNode->nextnode){
                tailNode->prenode->nextnode = nullptr;
                this->blockMap[tailNode->x][tailNode->y] = 6;
                break;
            }
            tailNode = tailNode->nextnode;
        }
    }
}

//使用算法算出头结点下一位置
std::shared_ptr<Node> blockmap::search()
{

    std::queue<std::shared_ptr<Node>> q;
    q.push(this->head);
    this->visit[this->head->x][this->head->y]=1;//初始化头结点visit
    while(!q.empty()){
        std::shared_ptr<Node> node = q.front();
        //this->travelsal();
        //std::cout<<node<<"\n";
        q.pop();
        if(node->x==this->target->x && node->y==this->target->y){ //如果当期结点是target,则回溯并返回pathHead指向的下一结点
            //对node链表的pre和next进行重置
            node->nextnode=node->prenode;
            node->prenode = nullptr;
            std::shared_ptr<Node> temp_node = node;
            if(node->nextnode == this->head){
                return node;
            }else{
                node = node->nextnode;
            }
            while(node){
                node->nextnode = node->prenode;
                if(node->nextnode == this->head){
                    node->prenode = temp_node;
                    return node;
                }else{
                    node->prenode = temp_node;
                    temp_node = node;
                    node = node->nextnode;
                }
            }
        }
        else{
            if(checkNodeAvailability(node->x-1,node->y) && this->visit[node->x-1][node->y]==0){
                //std::auto_ptr<Node> p(this->createNodePtr());
                q.push(std::shared_ptr<Node>(new Node(node->x-1,node->y,node,nullptr)));
                this->visit[node->x-1][node->y]=1;
            };
            if(checkNodeAvailability(node->x+1,node->y) && this->visit[node->x+1][node->y]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x+1,node->y,node,nullptr)));
                this->visit[node->x+1][node->y]=1;
            };
            if(checkNodeAvailability(node->x,node->y+1) && this->visit[node->x][node->y+1]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x,node->y+1,node,nullptr)));
                this->visit[node->x][node->y+1]=1;
            };
            if(checkNodeAvailability(node->x,node->y-1) && this->visit[node->x][node->y-1]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x,node->y-1,node,nullptr)));
                this->visit[node->x][node->y-1]=1;
            };
        }
    }
    return nullptr;
}


bool blockmap::checkNodeAvailability(int x, int y)
{
    if(this->blockMap[x][y]==6 || this->blockMap[x][y]==0){
        return true;
    }
    else{
        return false;
    }
}

void blockmap::generateTarget()
{
    int a = this->width;
    int b = this->height;
    srand((unsigned)time(NULL)); //初始化随机数种子
    int rw,rh;
    for(int i=0;i<20;i++){
        rw = (rand() % (a));
        rh = (rand() % (b));
        if(this->blockMap[rh][rw]==6){
            break;
        }
    }
    this->target = std::shared_ptr<Node>(new Node(rh,rw,0));
    this->blockMap[rh][rw]=0;
}

void blockmap::travelsal()
{
    system("cls");
    int height = this->height;
    int width = this->width;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            std::cout<<this->visit[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

int blockmap::getDirection(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
{
    if(n1->x == n2->x && (n1->y -n2->y) == 1){
        return 3; // 右
    }
    if(n1->x == n2->x && (n1->y - n2->y) == -1){
        return 5; // 左
    }
    if(n1->y == n2->y && (n1->x - n2->x) == 1){
        return 4; // 右
    }
    if(n1->y == n2->y && (n1->x - n2->x) == -1){
        return 2; // 左
    }
}

