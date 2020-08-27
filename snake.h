#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QList>
#include <QPoint>
#include "utils.h"
#include <QDebug>

class Snake : public QObject{
    Q_OBJECT
public:
    int len() const {return body.length();}
    int dir() const {return m_dir;}
    int grow() const {return m_grow;}
    void setgrow(int);

    Snake(QObject* parent = 0);

signals:
    void snakeMoved(QPoint,QPoint);
    void snakeRetracted(QPoint);

public slots:
    void retract();
    void move();
    void chgDirection(int);
    void init();

private:
    QList<QPoint> body;
    int m_dir;
    int m_grow;
    bool dirChanged;
};

#endif // SNAKE_H
