#include "cell.h"

Cell::Cell(int s, QPoint pos, QWidget *parent)
    : QPushButton(parent),
      m_status((cellStatus)s),
      m_pos(pos)
{
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    setMaximumSize(20,20);
    connect(this,SIGNAL(clicked()),this,SLOT(handleClick()));
    setFocusPolicy(Qt::NoFocus);
    m_style = 0;
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

void Cell::setBlankStyle(bool set){
    m_style = set;
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
    /*
    QPainter p(this);
    p.setPen(Qt::darkGray);
    QColor color;
    switch (m_status) {
    case blank: {
        color = QColor(Qt::white);
        p.setPen(Qt::NoPen);
        break;
    }
    case block: color = QColor(Qt::darkGray);break;
    case snake_body: color = QColor(Qt::black);break;
    case snake_head: color = QColor(Qt::blue);break;
    case apple: color = QColor(Qt::red);break;
    }
    p.setBrush(color);
    QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
    p.drawRect(rec);
    */

    QPainter p(this);
    QColor grass(173,238,146,80), stone(114,118,114), snakebody(47,70,63), snakehead(0,128,0);
    switch (m_status) {
    case 0: // blank
    {
        if(!m_style){
            p.setPen(Qt::darkGray);
            p.setBrush(grass);
            QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
            p.drawRect(rec);
        }else{
            p.setPen(Qt::NoPen);
            p.setBrush(grass);
            p.drawRect(rect());
        }
        break;
    }
    case 1:     // block
    {
        p.setPen(Qt::darkGray);
        p.setBrush(stone);
        QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
        p.drawRect(rec);
        break;
    }
    case 2: //snake_body
    {
        p.setPen(Qt::darkGreen);
        p.setBrush(snakebody);
        QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
        p.drawRect(rec);
        break;
    }
    case 3: // snake_head
    {
        p.setPen(Qt::green);
        p.setBrush(snakehead);
        QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
        p.drawRect(rec);
        break;
    }
    case 4: // apple
    {
        p.setPen(Qt::NoPen);
        p.setBrush(grass);
        p.drawRect(rect());
        p.setPen(Qt::darkGray);
        p.setBrush(Qt::red);
        QRect rec(rect().x()+1,rect().y()+1,rect().width()-2,rect().height()-2);
        p.drawEllipse(rec);
        break;
    }
    }
}

void Cell::changeCellStatus(QPoint pos, int status)
{
    if(pos == m_pos)
    {
        m_status = (cellStatus)status;
        update();
    }
}
