#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include "cell.h"
#include <QGridLayout>
#include <QtMath>
#include <QDebug>

class board : public QWidget
{
    Q_OBJECT
public:
    explicit board(QWidget *parent = nullptr);
    Cell* getCell(int i,int j) const {return cells[i][j];}

signals:
    void chgCellStatus(QPoint,int);
    void hit();
    void appleEaten();

public slots:
    void SnakeMoved(QPoint preH,QPoint tryH);
    void SnakeRetracted(QPoint);
    //void ExtractBoardStatus();
    void flush();
    void genApple();
    void setCellsDisable(bool);

private:

    QGridLayout *layout;
    Cell *cells[SIZE][SIZE];
};

#endif // BOARD_H
