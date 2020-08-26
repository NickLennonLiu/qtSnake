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
    body.append(QPoint(0,0));
    body.append(QPoint(0,1));
    m_dir = 2;
    m_grow = 0;
}

