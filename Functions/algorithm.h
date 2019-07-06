#include "../Global/header.h"
/*
    统计模拟跑到目的地的步长，算法与riderMove同
*/
int virtualRun(int *cur_x, int *cur_y, int pos_x, int pos_y)
{
    int cnt = 0;
    while (abs((*cur_x) - pos_x) > 1 || abs((*cur_y) - pos_y) > 1)
    {
        i = *cur_x;
        j = *cur_y;
        cnt++;
        // 先左右
        if (*cur_y < pos_y - 1 || *cur_y > pos_y + 1)
        {
            if (i % 2 == 1 && j % 2 == 0) // 在横向道路上
            {
                if (*cur_y > pos_y + 1) // 在右边就要往左走
                    (*cur_y) -= 2;
                else if (*cur_y < pos_y - 1) // 在左边要往右走
                    (*cur_y) += 2;
            }
            else if (i % 2 == 0 && j % 2 == 1) // 在纵向道路上
            {
                if (*cur_y > pos_y + 1) // 在右边就要往左走
                {
                    if (pos_x >= *cur_x) // 目标在下或同行
                    {
                        (*cur_x)++;
                        (*cur_y)--;
                    }
                    else if (pos_x < *cur_x) // 目标在上
                    {
                        (*cur_x)--;
                        (*cur_y)--;
                    }
                }
                else if (*cur_y < pos_y + 1) // 在右边就要往左走
                {
                    if (pos_x >= *cur_x) // 目标在下或同行
                    {
                        (*cur_x)++;
                        (*cur_y)++;
                    }
                    else if (pos_x < *cur_x) // 目标在上
                    {
                        (*cur_x)--;
                        (*cur_y)++;
                    }
                }
            }
        }
        // 后上下
        else if (i < pos_x - 1 || i > pos_x + 1)
        {
            if (i % 2 == 0 && j % 2 == 1) // 在纵向道路上
            {
                if (*cur_x > pos_x + 1) // 在下边就要往上走
                    (*cur_x) -= 2;
                else if (*cur_x < pos_x - 1) // 在上边要往下走
                    (*cur_x) += 2;
            }
            else if (i % 2 == 1 && j % 2 == 0) // 在横向道路上
            {
                if (*cur_x > pos_x + 1) // 在下边就要往上走
                {
                    if (pos_y >= *cur_y) // 目标在右或同列
                    {
                        (*cur_y)++;
                        (*cur_x)--;
                    }
                    else if (pos_y < *cur_y) // 目标在左
                    {
                        (*cur_y)--;
                        (*cur_x)--;
                    }
                }
                if (*cur_x < pos_x + 1) // 在上边就要往下走
                {
                    if (pos_y >= *cur_y) // 目标在右或同列
                    {
                        (*cur_y)++;
                        (*cur_x)++;
                    }
                    else if (pos_y < *cur_y) // 目标在左
                    {
                        (*cur_y)--;
                        (*cur_x)++;
                    }
                }
            }
        }
    }
    return cnt;
}
/*
    获取两点之间的曼哈顿距离
 */
int getDis(int a_x, int a_y, int b_x, int b_y)
{
    return abs(a_x - b_x) + abs(a_y - b_y);
}
/*
    模拟跑一遍当前队列加拟加订单，算出花费
    API: Rider *, Order *
    return: int
 */
int getPath(Rider *nowRider, Order *nowOrder)
{
    int sum = 0;
    int now_x = nowRider->rider_x, now_y = nowRider->rider_y, nxt_x, nxt_y;
    OrderList *nowBag = nowRider->Bag->Nxt_order;
    while (nowBag)
    {
        if (nowBag->Cur_order->status == 1)
            sum += virtualRun(&now_x, &now_y, nowBag->Cur_order->rest_x, nowBag->Cur_order->rest_y);
        else if (nowBag->Cur_order->status == 2)
            sum += virtualRun(&now_x, &now_y, nowBag->Cur_order->cust_x, nowBag->Cur_order->cust_y);
        nowBag = nowBag->Nxt_order;
    }
    sum += virtualRun(now_x, now_y, nowOrder->rest_x, nowOrder->rest_y);
    return sum;
}