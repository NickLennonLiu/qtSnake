#ifndef SNAKERE_H
#define SNAKERE_H
#include <QObject>
#include <QList>
#include <QPoint>
class Snake : public QObject{
    Snake(QObject* parent = 0);
    ~Snake();
public:
    int len() const {return body.length();}
    int dir() const {return m_dir;}
    int grow() const {return m_grow;}
    void setgrow(int);
    void init();

signals:
    void snakeMoved(QPoint);
    void snakeRetracted(QPoint);

public slots:
    void retract();
    void move();
    void chgDirection(int);

private:
    QList<QPoint> body;
    int m_dir;
    int m_grow;
};

#endif // SNAKERE_H
