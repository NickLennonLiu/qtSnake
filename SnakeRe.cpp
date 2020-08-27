#include "SnakeRe.h"

Snake::Snake(QObject* parent)
    : QObject(parent)
{
    init();
}

void Snake::setgrow(int grow) {m_grow = grow;}

void Snake::init()
{
    body.clear();
    body.append(QPoint(20,10));
    body.append(QPoint(20,11));
    m_dir = 2;
    m_grow = 0;
    emit snakeMoved(QPoint(20,10),QPoint(20,11));
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
    emit snakeMoved(head,next);
}

void Snake::chgDirection(int dir) {m_dir = dir;}
