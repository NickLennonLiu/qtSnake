#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "cell.h"
#include <QPainter>
#include <QGridLayout>
#include <QFrame>
#include <QDebug>
#include <QTimer>

const int SIZE = 40;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setWindowTitle("Snake");
    setFixedSize(QSize(820,870));

    init();

}

void GameWindow::init(){


    connect(ui->actionStart,&QAction::triggered,[=](){ emit actionTriggered(1);});
    connect(ui->actionPause,&QAction::triggered,[=](){ emit actionTriggered(2);});
    connect(ui->actionContinue,&QAction::triggered,[=](){ emit actionTriggered(1);});
    connect(ui->actionRestart,&QAction::triggered,[=](){ emit actionTriggered(0);});
    connect(ui->actionSave,&QAction::triggered,[=](){ emit actionTriggered(2);});
    connect(ui->actionLoad,&QAction::triggered,[=](){ emit actionTriggered(2);});
    connect(this,&GameWindow::actionTriggered,this,&GameWindow::gameStatusChange);
    gameStatusChange(0);

    int width = 800;
    gameboard = new board(ui->centralwidget);
    gameboard->setGeometry(10,10,width,width);
    gameboard->show();

    snake = new Snake()

    playTimer = new QTimer(this);
    playTimer->setInterval(1000);
    connect(playTimer,SIGNAL(timeout()),this,SLOT(playStep()));

}

void GameWindow::setInitGame(){
    gameboard->boardInit();

}

void GameWindow::playStep()
{

}

GameWindow::~GameWindow()
{
    delete ui;
}


void GameWindow::gameStatusChange(int status){
    ui->actionStart->setDisabled(status_map[status][0]);
    ui->actionPause->setDisabled(status_map[status][1]);
    ui->actionContinue->setDisabled(status_map[status][2]);
    ui->actionRestart->setDisabled(status_map[status][3]);
    ui->actionSave->setDisabled(status_map[status][4]);
    ui->actionLoad->setDisabled(status_map[status][5]);
    m_mainStatus = status;
    switch(status){
    case 0: //未开始
    case 1: //游戏状态
    case 2: //暂停状态
    case 3: //停止状态
    default: break;
    }
}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    if(m_mainStatus!=1){
        QMainWindow::keyPressEvent(ev);
        return;
    }
    switch(ev->key()){
    case Qt::Key_Right: emit direcInput(0);break;
    case Qt::Key_Left: emit direcInput(1);break;
    case Qt::Key_Down: emit direcInput(2);break;
    case Qt::Key_Up: emit direcInput(3);break;
    default: QMainWindow::keyPressEvent(ev);
    }
}
