#include "snake.h"

Snake::Snake(QObject* parent)
    : QObject(parent)
{
    //init();
    re.setMedia(QUrl("qrc:/direction/sounds/re.wav"));
    mi.setMedia(QUrl("qrc:/direction/sounds/mi.wav"));
    sol.setMedia(QUrl("qrc:/direction/sounds/sol.wav"));
    la.setMedia(QUrl("qrc:/direction/sounds/la.wav"));
}

void Snake::setgrow(int grow) {m_grow = grow;}

void Snake::init()
{
    body.clear();
    body.append(QPoint(SIZE/2,SIZE/2));
    body.append(QPoint(SIZE/2,SIZE/2 + 1));
    m_dir = 0;
    m_grow = 0;
    qDebug() << "Generated snake";
    emit snakeMoved(QPoint(SIZE/2,SIZE/2),QPoint(SIZE/2,SIZE/2 + 1));
    dirChanged = 0;
}

void Snake::retract()
{
    QPoint tail = body.front();
    body.pop_front();
    emit snakeRetracted(tail);
}

void Snake::move()
{
    QPoint head = body.back();
    QPoint next = head + direct[m_dir];
    body.push_back(next);
    dirChanged = 0;
    emit snakeMoved(head,next);
}

void Snake::chgDirection(int dir,bool forced) {
    if(forced){
        m_dir = dir;
        return;
    }
    if(((m_dir + dir)%2) && !dirChanged)
    {
        m_dir = dir;
        switch (dir) {
        case 0:re.stop();re.play();break;
        case 1:mi.stop();mi.play();break;
        case 2:sol.stop();sol.play();break;
        case 3:la.stop();la.play();break;
        }
        dirChanged = 1;
    }

}

void Snake::clear()
{
    body.clear();
}

void Snake::appendBody(QPoint part)
{
    body.append(part);
}
