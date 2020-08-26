#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include "cell.h"
#include <QGridLayout>
#include <QtMath>

class board : public QWidget
{
    Q_OBJECT
public:
    explicit board(QWidget *parent = nullptr);

signals:
    void chgCellStatus(QPoint,int);
    void hit();
    void appleEaten();

public slots:
    void SnakeMoved(QPoint preH,QPoint tryH);
    void SnakeRetracted(QPoint);
    void ExtractBoardStatus();


private:
    void genApple();
    QGridLayout *layout;
    Cell *cells[40][40];
};

#endif // BOARD_H
