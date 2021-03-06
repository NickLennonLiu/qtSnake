#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "utils.h"
#include "board.h"
#include "snake.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "about.h"
#include "help.h"
#include <QSizePolicy>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:

    void gameStatusChange(int);

    void playStep();
    void playStart();
    void playPause();
    void playRestart();
    void playEnd();
    void playLaunch();

    void snakeGrow();

    void saveGame();
    void loadGame();

    void viewHelp();
    void viewAbout();

    void chgSpeed(float);

signals:
    void actionTriggered(int);
    void direcInput(int);
    void snakeMove();
    void snakeRetract();

private:
    Ui::GameWindow *ui;

    void keyPressEvent(QKeyEvent *ev) override;
    bool eventFilter(QObject* obj, QEvent *ev) override;

    void init();
    void setInitGame();

    int m_mainStatus;
    QTimer* playTimer;
    board* gameboard;
    Snake* snake;
    int m_prepared;

};
#endif // GAMEWINDOW_H
