#include "board.h"

board::board(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    for(int i = 0;i<40;i++){
        for(int j = 0;j<40;j++){
            cells[i][j] = new Cell(0,QPoint(i,j));
            connect(this,SIGNAL(chgCellStatus(QPoint,int)),cells[i][j],SLOT(changeCellStatus(QPoint,int)));
            layout->addWidget(cells[i][j],i,j);
        }
    }
    layout->setSpacing(0);
    this->setLayout(layout);
}

void board::SnakeMoved(QPoint preH,QPoint tryH)
{
    int x = tryH.x(),y = tryH.y();
    if( x < 0 || x >=40 || y < 0 || y >= 40){
        emit hit();
        return;
    }
    cellStatus cell = cells[x][y]->getStatus();
    switch(cell){
    case blank:{emit chgCellStatus(preH,2);emit chgCellStatus(tryH,3);break;}
    case block:{emit hit();break;}
    case snake_body:{emit hit();break;}
    case snake_head:{emit hit();break;}
    case apple:{emit appleEaten();break;}
    }
}

void board::SnakeRetracted(QPoint pos){
    emit chgCellStatus(pos,0);
}

void board::genApple(){
    int x = qrand()%40, y = qrand()%40;
    while(cells[x][y]->getStatus() != blank){
        x = qrand()%40, y = qrand()%40;
    }
    emit chgCellStatus(QPoint(x,y),4);
}
