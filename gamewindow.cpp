#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "cell.h"
#include <QPainter>
#include <QGridLayout>
#include <QFrame>
#include <QDebug>
#include <QTimer>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{

    installEventFilter(this);
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    setWindowTitle("Snake");
    setFixedSize(QSize(820,870));
    //ui->statusHint->setStyleSheet("border:none");

    init();

}

void GameWindow::init(){
    connect(ui->actionStart,&QAction::triggered,[=](){ emit actionTriggered(1);playStart();});
    connect(ui->actionPause,&QAction::triggered,[=](){ emit actionTriggered(2);playPause();});
    connect(ui->actionContinue,&QAction::triggered,[=](){ emit actionTriggered(1);m_prepared = 1;playLaunch();});
    connect(ui->actionRestart,&QAction::triggered,[=](){ emit actionTriggered(0);playRestart();});
    connect(ui->actionSave,&QAction::triggered,[=](){ emit actionTriggered(2);saveGame();});
    connect(ui->actionLoad,&QAction::triggered,[=](){ /*emit actionTriggered(2);*/loadGame();});
    connect(this,&GameWindow::actionTriggered,this,&GameWindow::gameStatusChange);
    connect(ui->actionView_Help,&QAction::triggered,[=](){ viewHelp();});
    connect(ui->actionAbout,&QAction::triggered,[=](){ viewAbout();});
    gameStatusChange(0);

    int width = 800;
    gameboard = new board();
    ui->verticalLayout->addWidget(gameboard);
    gameboard->setGeometry(10,10,width,width);
    gameboard->show();

    snake = new Snake();

    connect(this,SIGNAL(direcInput(int)),snake,SLOT(chgDirection(int)));
    connect(this,SIGNAL(snakeMove()),snake,SLOT(move()));
    connect(this,SIGNAL(snakeRetract()),snake,SLOT(retract()));

    connect(gameboard,SIGNAL(appleEaten()),this,SLOT(snakeGrow()));
    connect(gameboard,SIGNAL(hit()),this,SLOT(playEnd()));

    connect(snake,SIGNAL(snakeMoved(QPoint,QPoint)),gameboard,SLOT(SnakeMoved(QPoint,QPoint)));
    connect(snake,SIGNAL(snakeRetracted(QPoint)),gameboard,SLOT(SnakeRetracted(QPoint)));

    playTimer = new QTimer(this);
    playTimer->setInterval(100);
    connect(playTimer,SIGNAL(timeout()),this,SLOT(playStep()));

    setInitGame();
}

void GameWindow::setInitGame(){
    ui->timeLCD->display(0);
    ui->appleLCD->display(0);
    gameboard->flush();
    gameboard->genApple();
    snake->init();
    m_prepared = 0;
}

void GameWindow::playStart(){
    //playTimer->start();
    gameboard->setCellsDisable(true);
    m_prepared = 1;
}

void GameWindow::playLaunch(){
    if(m_prepared){
        playTimer->start();
        ui->statusHint->setText("Good Luck!");
        m_prepared = 0;
    }
}

void GameWindow::playStep()
{
    ui->timeLCD->display(ui->timeLCD->value() + 1);
    emit snakeMove();
    if(snake->grow()){
        snake->setgrow(snake->grow() - 1);
    } else {
        if(m_mainStatus!=1) return;
        emit snakeRetract();
    }
}
void GameWindow::playPause()
{
    playTimer->stop();
}

void GameWindow::playRestart()
{
    setInitGame();
    gameboard->setCellsDisable(false);
}

void GameWindow::playEnd()
{
    qDebug() << "HIT! game ended";
    playTimer->stop();
    emit actionTriggered(3);
    QMessageBox* endGame = new QMessageBox(QMessageBox::Icon(0),tr("GameOver!"),tr("Game over! Try Again?"),QMessageBox::Yes|QMessageBox::No,this);
    if(endGame->exec() == QMessageBox::Yes){
        actionTriggered(0);
        playRestart();
    }

}

void GameWindow::snakeGrow()
{
    ui->appleLCD->display(ui->appleLCD->value() + 1);
    snake->setgrow(3);
    gameboard->genApple();
}

void GameWindow::saveGame(){
    QString filename = QFileDialog::getSaveFileName(this,tr("保存"),"","save (*.save)");
    QFile saveFile(filename);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        qDebug() << "open file failed!";
    } else {
        qDebug() << "open file success!";
    }
    QTextStream output(&saveFile);

    output << ui->timeLCD->value() << " "
           << ui->appleLCD->value() << endl << endl;

    for(int i = 0;i<SIZE ;i++){
        for(int j = 0;j < SIZE;j++){
            output << gameboard->getCell(i,j)->getStatus() << " ";

        }
        output << endl;
    }
    output << endl;
    QList<QPoint> snakebody = snake->getSnake();

    output << snake->len() << endl;
    for(auto i : snakebody){
        output << i.x() << " " << i.y() << endl;
    }
    output << endl;
    output << snake->grow()
           << " " << snake->dir() << endl;
    saveFile.close();
}

void GameWindow::loadGame(){


    QString filename = QFileDialog::getOpenFileName(this,tr("载入存档"),"",tr("save (*.save)"));
    QFile saveFile(filename);
    if(!saveFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "open file failed!";
        return;
    } else {
        qDebug() << "open file success!";
    }
    QTextStream input(&saveFile);

    gameboard->flush();
    snake->clear();

    int step,apple;
    input >> step >> apple;
    ui->timeLCD->display(step);
    ui->appleLCD->display(apple);

    int status;
    for(int i = 0;i<SIZE ;i++){
        for(int j = 0;j < SIZE;j++){
            input >> status;
            gameboard->chgCellStatus(QPoint(i,j),status);
        }
    }

    int len, x, y;
    input >> len;
    while(len--){
        input >> x >> y;
        snake->appendBody(QPoint(x,y));
        qDebug() << "snake body appended:" << x << " " << y;
    }

    int grow, direction;
    input >> grow >> direction;
    snake->setgrow(grow);
    snake->chgDirection(direction,true);

    saveFile.close();
    emit actionTriggered(2);
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
    qDebug()<<"game status changed:" << m_mainStatus;
    switch(status){
    case 0: {   // 未开始状态
        ui->statusHint->setText("Press Enter to play.");
        break;
    }
    case 1: {   // 游戏状态
        ui->statusHint->setText("Choose a direction to launch!");
        break;
    }
    case 2:{    // 暂停状态
        ui->statusHint->setText("Press space to continue.");
        break;
    }
    case 3: {   // 停止状态
        ui->statusHint->setText("Game Over! Press R to restart.");
        break;
    }
    default: break;
    }
}

void GameWindow::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << "key pressed" << ev->key();
    if(ev->key() == Qt::Key_Comma) chgSpeed(1.2);
    if(ev->key() == Qt::Key_Period) chgSpeed(0.8);
    if(m_mainStatus!=1){
        QMainWindow::keyPressEvent(ev);
        return;
    }
    switch(ev->key()){
    case Qt::Key_D:
    case Qt::Key_Right: emit direcInput(0);emit playLaunch();qDebug()<<"turn right";break;
    case Qt::Key_A:
    case Qt::Key_Left: emit direcInput(2);emit playLaunch();qDebug()<<"turn left";break;
    case Qt::Key_S:
    case Qt::Key_Down: emit direcInput(1);emit playLaunch();qDebug()<<"turn down";break;
    case Qt::Key_W:
    case Qt::Key_Up: emit direcInput(3);emit playLaunch();qDebug()<<"turn up";break;
    default: QMainWindow::keyPressEvent(ev);
    }
}

bool GameWindow::eventFilter(QObject *watched, QEvent *event)
{
    return false;
}

void GameWindow::viewHelp()
{
    Help* help = new Help(this);
    help->exec();
}

void GameWindow::viewAbout()
{
    About* about = new About(this);
    about->exec();
}

void GameWindow::chgSpeed(float delta){
    int newInterval = (10>playTimer->interval() * delta)?10:playTimer->interval() * delta;
    newInterval = (newInterval < 1500)?newInterval:1500;
    playTimer->setInterval(newInterval);
}
