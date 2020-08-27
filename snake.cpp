#include "snake.h"

Snake::Snake(QObject* parent)
    : QObject(parent)
{
    //init();
}

void Snake::setgrow(int grow) {m_grow = grow;}

void Snake::init()
{
    body.clear();
    body.append(QPoint(20,10));
    body.append(QPoint(20,11));
    m_dir = 0;
    m_grow = 0;
    qDebug() << "Generated snake";
    emit snakeMoved(QPoint(20,10),QPoint(20,11));
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
