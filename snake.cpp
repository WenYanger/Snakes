#include "snake.h"

Snake::Snake()
{

}

Snake::Snake(int x, int y, int type) : head(std::shared_ptr<Node>(new Node(x,y,type)))
{}

void Snake::setBlockMap(BlockMap *bm)
{
    this->blockmap = bm;
}

void Snake::reSearchPath()
{
    //2. 使用算法改变snake状态
    this->path = this->search();
    this->visitReflush();

}

bool Snake::nextStep()
{
    //1. 判断是否还有target,没有则给定新的target
    if(!this->blockmap->target){
        this->generateTarget();

        //this->target = std::shared_ptr<Node>(new Node(5,5,0));
        //this->blockMap[5][5]=0;
    }
    //std::cout<<this->blockmap->target;
    std::cout<<this->head;

    //2. 使用算法改变snake状态
    if(!this->path){
        this->path = this->search();
        this->visitReflush();
    }
    //沿着path前进一格
    std::shared_ptr<Node> nextNode = this->path;
    if(!nextNode){
        return true;
    }


    //如果下一结点正好是别的蛇的一部分，则重新计算路线
    if(!this->checkSnake(this->path)){
        if(nextNode->x == this->blockmap->target->x && nextNode->y == this->blockmap->target->y){
            //蛇长度+1
            this->length++;

            //处理头部方向问题
            int direction = this->getDirection(nextNode,this->head);
            this->head->setType(1);
            nextNode->setType(direction);
            this->head = nextNode;


            //重新指定target,发送notice给所有snake，重新计算路线
            this->blockmap->target = nullptr;
            this->generateTarget();
            this->blockmap->noticeAllSnakesForNewPath();
            return true;

        }
        this->blockmap->noticeAllSnakesForNewPath();
        return true;
    }

    this->path = this->path->prenode;
    if(nextNode->x == this->blockmap->target->x && nextNode->y == this->blockmap->target->y){
        //蛇长度+1
        this->length++;

        //TODO: 处理头部方向问题
        int direction = this->getDirection(nextNode,this->head);
        this->head->setType(1);
        nextNode->setType(direction);
        this->head = nextNode;


        //TODO: 重新指定target,发送notice给所有snake，重新计算路线
        this->blockmap->target = nullptr;
        this->generateTarget();
        this->blockmap->noticeAllSnakesForNewPath();
        return true;
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
        std::shared_ptr<Node> tailNode = this->head;
        int length = 1;
        while(tailNode){
            if(!tailNode->nextnode){
                tailNode->prenode->nextnode = nullptr;
                this->blockmap->blockMap[tailNode->x][tailNode->y] = 6;
                break;
            }
            tailNode = tailNode->nextnode;
            length++;
        }
        std::cout<<"length :"<<length<<" ActualLength: "<<this->length<<std::endl;
        if(this->length != length-1){
            std::shared_ptr<Node> fixTailNode = this->head;
            for(int i=0;i<this->length;i++){
                if(i == this->length-1){
                    this->blockmap->blockMap[fixTailNode->nextnode->x][fixTailNode->nextnode->y] = 6;
                    fixTailNode->nextnode = nullptr;
                    break;
                }
                fixTailNode = fixTailNode->nextnode;
            }
        }
    }
    //将当期snake的最新位置信息更新到blockmap中
    this->snakeReflush();
}

//使用算法算出头结点下一位置
std::shared_ptr<Node> Snake::search()
{
    std::queue<std::shared_ptr<Node>> q;
    q.push(this->head);
    //this->blockmap->visit[this->head->x][this->head->y]=1;//初始化头结点visit
    while(!q.empty()){
        std::shared_ptr<Node> node = q.front();
        //this->travelsal();
        //std::cout<<node<<"\n";
        q.pop();
        if(node->x==this->blockmap->target->x && node->y==this->blockmap->target->y){ //如果当期结点是target,则回溯并返回pathHead指向的下一结点
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
            if(checkNodeAvailability(node->x-1,node->y) && this->blockmap->visit[node->x-1][node->y]==0){

                q.push(std::shared_ptr<Node>(new Node(node->x-1,node->y,node,nullptr)));
                this->blockmap->visit[node->x-1][node->y]=1;
            };
            if(checkNodeAvailability(node->x+1,node->y) && this->blockmap->visit[node->x+1][node->y]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x+1,node->y,node,nullptr)));
                this->blockmap->visit[node->x+1][node->y]=1;
            };
            if(checkNodeAvailability(node->x,node->y+1) && this->blockmap->visit[node->x][node->y+1]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x,node->y+1,node,nullptr)));
                this->blockmap->visit[node->x][node->y+1]=1;
            };
            if(checkNodeAvailability(node->x,node->y-1) && this->blockmap->visit[node->x][node->y-1]==0){
                q.push(std::shared_ptr<Node>(new Node(node->x,node->y-1,node,nullptr)));
                this->blockmap->visit[node->x][node->y-1]=1;
            };
        }
    }
    return nullptr;
}

void Snake::snakeReflush()
{
    std::shared_ptr<Node> cn = this->head; //cn=CurrentNode
    this->blockmap->blockMap[cn->x][cn->y]=cn->type;
    while(cn=cn->nextnode){
        this->blockmap->blockMap[cn->x][cn->y]=1;
    }
}

void Snake::visitReflush()
{
    int height = this->blockmap->height;
    int width = this->blockmap->width;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            this->blockmap->visit[i][j] = 0;
        }
    }
}

void Snake::generateTarget()
{
    int a = this->blockmap->width;
    int b = this->blockmap->height;
    srand((unsigned)time(NULL)); //初始化随机数种子
    int rw,rh;
    for(int i=0;i<20;i++){
        rw = (rand() % (a));
        rh = (rand() % (b));
        if(this->blockmap->blockMap[rh][rw]==6){
            break;
        }
    }
    this->blockmap->target = std::shared_ptr<Node>(new Node(rh,rw,0));
    this->blockmap->blockMap[rh][rw]=0;
}

bool Snake::checkNodeAvailability(int x, int y)
{
    if(this->blockmap->blockMap[x][y]==6 || this->blockmap->blockMap[x][y]==0){
        return true;
    }
    else{
        return false;
    }
}

int Snake::getDirection(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2)
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

bool Snake::checkSnake(std::shared_ptr<Node> n)
{
    int x = n->x;
    int y = n->y;
    if(this->blockmap->blockMap[x][y] == 6 || this->blockmap->blockMap[x][y] == 0){
        return true;
    }
    else{
        return false;
    }
}
