#include <QCoreApplication>
#include <snake.h>
#include <blockmap.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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
    Snake * s1 = new Snake(1,1,4);
    Snake * s2 = new Snake(5,5,4);
    Snake * s3 = new Snake(10,10,4);
    Snake * s4 = new Snake(15,15,4);
    Snake **sa = new Snake*[4];
    sa[0] = s1;
    sa[1] = s2;
    sa[2] = s3;
    sa[3] = s4;

    int width = 30;
    int height = 30;
    int numOfSnake = 4;
    BlockMap * bm = new BlockMap(sa,numOfSnake,width,height);

    sa[0]->setBlockMap(bm);
    sa[1]->setBlockMap(bm);
    sa[2]->setBlockMap(bm);
    sa[3]->setBlockMap(bm);


    while(1){

        if(bm->autoReflush()){

            for(int i=0; i<numOfSnake; i++)
            {
                std::cout<<"Snake "<<i+1<<" ";
                sa[i]->nextStep();
                if(i==3)std::cout<<"Target:"<<bm->target;
            }
            Sleep(50);
        }
        system("cls");
    }

    return a.exec();
}
