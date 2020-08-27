#include "snake.h"

Snake::Snake(coord bodycoord[],int len, QObject *parent,int dir)
    : QObject(parent), direction(dir), length(len)
{
    for (int i = 0; i < len; i++)
    {
        body[i] = new SnakePart(bodycoord[i]);
    }
    for (int i = 0; i < len - 1; i++)
    {
        body[i]->setNext(body[i + 1]);
    }
    tail = body[0];
    head = body[len-1];
}

coord Snake::move() {
    SnakePart* newHead = new SnakePart(head->getPos() + direct[direction]);
    head->setNext(newHead);
    head = newHead;
    return head->getPos();
}

coord Snake::retract() {
    SnakePart* temp = tail;
    coord re = temp->getPos();
    tail = tail->nextPart();
    delete temp;
    return re;
}

void Snake::chgDirection(int dir) {
    direction = dir;
}

void Snake::setGrowStatus(int s) {
    growStatus = s;
}

Snake::~Snake() {
    SnakePart* cur = tail;
    while(cur->nextPart()){
        SnakePart* next = cur->nextPart();
        delete cur;
        cur = next;
    }
}

SnakePart::SnakePart()
{
}

SnakePart::SnakePart(coord pos, SnakePart* next)
    : pos(pos)
    , next(next)
{
}

void SnakePart::setNext(SnakePart* nex) {
    next = nex;
}
