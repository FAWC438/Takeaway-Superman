#include "./Global/header.h"

/*
    招募骑手,返回骑手的id，注意，前提条件是CompanyMoney>=400
    return(int):骑手的id
 */
int hireRider()
{
    CompanyMoney -= 300; // 扣钱
    CompanyRiderCount++; // 加骑手数量
    Rider *newRider = (Rider *)malloc(sizeof(Rider));
    // 初始化新骑手
    newRider->id = CompanyRiderCount;
    newRider->rider_x = COMPANY_X;
    newRider->rider_y = COMPANY_Y;
    newRider->Bag = creatOrderList(); // 骑手的背包是一个订单链表
    //将该骑手添加到骑手列表
    push_back_rider(newRider, AllRiderLog);
    return newRider->id;
}
/*
    输入骑手id返回Order指针
    int rider_id:骑手id
    return(Order *):棋手当前订单的指针
 */
Order *getRiderCurOrder(int rider_id)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    return p->Cur_rider;
}
/*
    输入骑手id返回OrderList指针
    int rider_id:骑手id
    return(OrderList *):棋手当前背包的指针
 */
OrderList *getRiderCurBag(int rider_id)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    return p->Cur_rider->Bag;
}

/*
    返回骑手位置，注意传入的坐标为指针
    int rider_id:骑手id
    int *x:骑手横坐标指针
    int *y:骑手纵坐标指针
 */
void getRiderCurPos(int rider_id, int *x, int *y)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    *x = p->Cur_rider->rider_x;
    *y = p->Cur_rider->rider_y;
}
/*
    根据骑手id和目的地（房子坐标），根据骑手当前位置，先左右,后上下，移动一个单位
    int rider_id:骑手id
    int pos_x:目的地横坐标
    int pos_y:目的地纵坐标
 */
void riderMove(int rider_id, int pos_x, int pos_y)
{
    int *cur_x, *cur_y;
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    *cur_x = p->Cur_rider->rider_x;
    *cur_y = p->Cur_rider->rider_y;
    // TODO: 测试移动单元
    // 先左右
    if (i % 2 == 1 && j % 2 == 0) // 在横向道路上
    {
        if (*cur_y > pos_y + 1) // 在右边就要往左走
        {
            (*cur_y) -= 2;
        }
        else if (*cur_y < pos_y - 1) // 在左边要往右走
        {
            (*cur_y) += 2;
        }
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
        if (*cur_y < pos_y + 1) // 在右边就要往左走
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
    // 后上下
    if (i % 2 == 0 && j % 2 == 1) // 在纵向道路上
    {
        if (*cur_x > pos_x + 1) // 在下边就要往上走
        {
            (*cur_x) -= 2;
        }
        else if (*cur_x < pos_x - 1) // 在上边要往下走
        {
            (*cur_x) += 2;
        }
    }
    else if (i % 2 == 0 && j % 2 == 1) // 在横向道路上
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
    else // 异常情况处理
    {
        // TODO: 加入终止函数？
        printf("咋骑手跑到房子里了？\n");
        //exit(0);
    }

    /* 
        横纵坐标一奇一偶的都是路，坐标都是偶数的是房间，坐标都是奇数的是路口
        房子上面和下面的路（横着的）：(偶，奇) 房子左面和右面的路（竖着的）：(奇，偶)
        TODO:更改骑手的位置，仅移动一个单位
     */
}
