#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QList>
#include <QPoint>
#include "utils.h"
#include <QDebug>
#include <QMediaPlayer>

class Snake : public QObject{
    Q_OBJECT
public:
    int len() const {return body.length();}
    int dir() const {return m_dir;}
    int grow() const {return m_grow;}

    QList<QPoint> getSnake() const {return body;}

    Snake(QObject* parent = 0);

signals:
    void snakeMoved(QPoint,QPoint);
    void snakeRetracted(QPoint);

public slots:
    void retract();
    void move();
    void setgrow(int);
    void chgDirection(int,bool forced = false);
    void init();
    void clear();
    void appendBody(QPoint);

private:
    QList<QPoint> body;
    int m_dir;
    int m_grow;
    bool dirChanged;
    QMediaPlayer re,mi,sol,la;

};

#endif // SNAKE_H
