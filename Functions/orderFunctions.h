#include "./Global/header.h"

void assignOrder(int RiderID)   //把队首订单放入对应骑手的背包
{
    Order * FrontOrder = pop_front_order(AllOrderLog);
    RiderList * FindRider = AllRiderLog->Nxt_rider;
    while(FindRider&&FindRider->Cur_rider->id!=RiderID)         //找到ID为RiderID的骑手
        FindRider = FindRider->Nxt_rider;
    if(FindRider==NULL)                        //判断是否能找到该骑手
        printf("骑手ID越界\n");                 //若找不到，返回错误信息
    else
        push_back_order(FrontOrder,FindRider->Cur_rider->Bag);  //将队首订单放入骑手背包
}

