#include "gamewindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow w;
    w.show();
    //w.move((QApplication::desktop()->width - w.wi))
    return a.exec();
}
