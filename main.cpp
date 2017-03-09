#include <QCoreApplication>
#include <blockmap.h>
#include <node.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    blockmap *mainMap = new blockmap(30,20);
    while(1){
        system("cls");
        if(mainMap->autoReflush()){
            Sleep(1000);
        }
    }

    return a.exec();
}
