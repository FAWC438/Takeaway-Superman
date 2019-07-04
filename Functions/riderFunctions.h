#include "./Global/header.h"

int hireRider() // 招募骑手,返回骑手的id，注意，前提条件是CompanyMoney>=400
{
    CompanyMoney -= 300;
    CompanyRiderCount++;
    RiderList *p = AllRiderLog, *tmp = (RiderList *)malloc(sizeof(RiderList));
    Rider *newRider = (Rider *)malloc(sizeof(Rider));
    while (p->Nxt_rider)
    {
        p = p->Nxt_rider;
    }
    // 初始化新骑手
    newRider->Cur_order = NULL;
    newRider->id = p->Cur_rider->id + 1;
    newRider->rider_x = COMPANY_X;
    newRider->rider_y = COMPANY_Y;
    newRider->Bag = creatOrderList(); // 骑手的背包是一个订单链表
    //将该骑手添加到骑手列表
    p->Nxt_rider = tmp;
    tmp->Pre_rider = p;
    tmp->Cur_rider = newRider;
    tmp->Nxt_rider = NULL;
    return newRider->id;
}