                                                                                                                                                                                                                                                                                                                                                                                                                    #include <QCoreApplication>
#include <blockmap.h>
#include <node.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    blockmap *mainMap = new blockmap(40,30);
    while(1){
        system("cls");
        if(mainMap->autoReflush()){
            Sleep(300);
        }
    }


    return a.exec();
}
