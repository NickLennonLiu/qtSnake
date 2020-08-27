#ifndef UTILS_H
#define UTILS_H


#include <QPoint>


QPoint const direct[4] = {QPoint(0,1),QPoint(1,0),QPoint(0,-1),QPoint(-1,0)};   // 0右 1下 2左 3上

// 0右 1下 2左 3上

enum cellStatus{
    blank, block, snake_body, snake_head, apple
};

const int status_map[4][6] = {
    {0,1,1,1,1,0},  // 0 未开始状态
    {1,0,1,1,1,1},  // 1 游戏状态
    {1,1,0,0,0,1},  // 2 暂停状态
    {1,1,1,0,1,1}   // 3 终止状态
};


#endif // UTILS_H
