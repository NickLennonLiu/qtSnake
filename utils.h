#ifndef UTILS_H
#define UTILS_H

struct coord
{
    int x;
    int y;
    coord operator+(coord const dir)
    {
        coord a;
        a.x = x + dir.x;
        a.y = y + dir.y;
        return a;
    }
};

coord const direct[4] = {{1,0},{-1,0},{0,1},{0,-1}};

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
