#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "utils.h"
#include <QPoint>

class Cell : public QPushButton
{
    Q_OBJECT
public:
    explicit Cell(int s, QPoint pos, QWidget *parent = nullptr);
    cellStatus getStatus() const {return m_status;};
    //QSize sizeHint() const override;
signals:

public slots:
    void changeCellStatus(QPoint,int);
    void handleClick();
    void setBlankStyle(bool);

private:
    void paintEvent(QPaintEvent *) override;
    cellStatus m_status;
    QPoint m_pos;
    int m_style;

};

#endif // CELL_H
