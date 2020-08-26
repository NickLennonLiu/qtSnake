#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "utils.h"
#include "board.h"
#include "snake.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int mainStatus)

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:

    void gameStatusChange(int);
    void playStep();

signals:
    void actionTriggered(int);
    void direcInput(int);

private:
    Ui::GameWindow *ui;

    void keyPressEvent(QKeyEvent *ev) override;

    void init();
    void setInitGame();

    int m_mainStatus;
    QTimer* playTimer;
    board* gameboard;
    Snake* snake;

};
#endif // GAMEWINDOW_H
