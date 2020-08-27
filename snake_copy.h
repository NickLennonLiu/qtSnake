#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "utils.h"


class SnakePart {
public:
    SnakePart();
    SnakePart(coord pos, SnakePart* next = 0);

    //int getX() const {return pos.x;}
    //int getY() const {return pos.y;}
    coord getPos() const {return pos;}

    SnakePart* nextPart() const {return next;}

    void setNext(SnakePart* next);

private:
    coord pos;
    SnakePart* next;
};


class Snake : public QObject{

    Q_OBJECT

public:
    explicit Snake(coord bodycoord[],int len,QObject *parent = nullptr,int dir = 0);
    ~Snake();
    int getGrowStatus() const {return growStatus;}

signals:
    void snakeMoved(coord);
    void snakeRetracted(coord);

public slots:
    coord retract();
    coord move();
    void chgDirection(int);
    void setGrowStatus(int);

private:

    SnakePart *body[1601], *tail, *head;
    int direction;
    int length;
    int growStatus;
};

#endif // SNAKE_H
