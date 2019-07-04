#include "./Global/header.h"

void assignOrder(Order *AOrder, int RiderID) //把订单放入对应骑手的背包
{
    RiderList *FindRider = AllRiderLog->Nxt_rider;
    while (FindRider && FindRider->Cur_rider->id != RiderID) //找到ID为RiderID的骑手
        FindRider = FindRider->Nxt_rider;
    if (FindRider == NULL) //判断是否能找到该骑手
    {
        printf("骑手ID越界\n"); //若找不到，返回错误信息
        return;
    }
    else
    {
        AOrder->status = 1;                                 //订单的状态变为“取餐”
        push_back_order(AOrder, FindRider->Cur_rider->Bag); //将订单放入骑手背包
    }
}
