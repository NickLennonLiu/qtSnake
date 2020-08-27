#include "cell.h"

Cell::Cell(int s, QPoint pos, QWidget *parent)
    : QPushButton(parent),
      m_status((cellStatus)s),
      m_pos(pos)
{
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    setMaximumSize(30,30);
    connect(this,SIGNAL(clicked()),this,SLOT(handleClick()));
    setFocusPolicy(Qt::NoFocus);
}

void Cell::handleClick()
{
    if(m_status == blank){
        m_status = block;
        update();
    } else if(m_status == block) {
        m_status = blank;
        update();
    }
}

/*
QSize Cell::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    size.rwidth() = 20;
    size.rheight() = 20;
    return size;
}
*/

void Cell::paintEvent(QPaintEvent *ev) {
    QPainter p(this);
    p.setPen(Qt::darkGray);
    QColor color;
    switch (m_status) {
    case blank: color = QColor(Qt::white);break;
    case block: color = QColor(Qt::darkGray);break;
    case snake_body: color = QColor(Qt::black);break;
    case snake_head: color = QColor(Qt::blue);break;
    case apple: color = QColor(Qt::red);break;
    }
    p.setBrush(color);
    QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
    p.drawRect(rec);
}

void Cell::changeCellStatus(QPoint pos, int status)
{
    if(pos == m_pos)
    {
        m_status = (cellStatus)status;
        update();
    }
}
