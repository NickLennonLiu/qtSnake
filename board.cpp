#include "board.h"

board::board(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;j<SIZE;j++){
            cells[i][j] = new Cell(0,QPoint(i,j));
            connect(this,SIGNAL(chgCellStatus(QPoint,int)),cells[i][j],SLOT(changeCellStatus(QPoint,int)));
            layout->addWidget(cells[i][j],i,j);
        }
    }
    layout->setSpacing(0);
    this->setLayout(layout);
}

void board::flush()
{
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;j<SIZE;j++){
            cells[i][j]->changeCellStatus(QPoint(i,j),0);
            cells[i][j]->setBlankStyle(0);
        }
    }
}

void board::SnakeMoved(QPoint preH,QPoint tryH)
{
    int x = tryH.x(),y = tryH.y();
    if( x < 0 || x >=SIZE || y < 0 || y >= SIZE){
        emit hit();
        qDebug() << "out of boundary!" << x << " " << y;
        return;
    }
    cellStatus cell = cells[x][y]->getStatus();
    switch(cell){
    case blank:{emit chgCellStatus(preH,2);emit chgCellStatus(tryH,3);break;}
    case block:{emit hit();qDebug()<<"hit block";break;}
    case snake_body:{emit hit();qDebug()<<"hit body";break;}
    case snake_head:{emit hit();qDebug()<<"hit head";break;}
    case apple:{emit chgCellStatus(preH,2);emit chgCellStatus(tryH,3);emit appleEaten();break;}
    }
}

void board::SnakeRetracted(QPoint pos){
    emit chgCellStatus(pos,0);
}

void board::genApple(){
    qsrand(time(0));
    int x = qrand()%SIZE, y = qrand()%SIZE;
    while(cells[x][y]->getStatus() != blank){
        x = qrand()%SIZE, y = qrand()%SIZE;
    }
    emit chgCellStatus(QPoint(x,y),4);
}

void board::setCellsDisable(bool dis)
{
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;j<SIZE;j++){
            cells[i][j]->setDisabled(dis);
            cells[i][j]->setBlankStyle(dis);
        }
    }
}
