#include "../Global/header.h"
/*
    把订单放入对应骑手的背包
    Var: Order类型订单、骑手ID
*/
void assignOrder(Order *AOrder, int RiderID)
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
        OrderList *nowOrder = AllOrderLog->Nxt_order;
        while(nowOrder)
        {
            if(nowOrder->Cur_order->id == AOrder->id)
            {
                nowOrder->Cur_order->status = 1;
                break;
            }
        }
        AOrder->status = 1;                                 //订单的状态变为“取餐”
        push_back_order(AOrder, FindRider->Cur_rider->Bag); //将订单放入骑手背包
    }
}
/*
    每次刷新时间点后判断是否有超时订单，若破产则结束游戏
*/
void isAnyOrderOverTime()
{
    OrderList *HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    while (HeadOrder)
    {
        if (HeadOrder->Cur_order->status == 3) // 不处理已完成订单
            continue;
        int difference = Time - HeadOrder->Cur_order->begin_time;             // 时间差
        if (difference == DEAD_TIME + 1 && HeadOrder->Cur_order->status == 0) //拒单
            // printf("GAMEOVER!!!\n");
            gameOver(1);
        if (difference == FINE_SECOND_TIME + 1) // 恶意拖单
            // printf("GAMEOVER!!!\n");
            gameOver(2);
        else if (difference == FINE_FIRST_TIME + 1) // 罚单,资金为负
        {
            CompanyMoney -= FINE_MONEY;
            CompanyOrderOverTime++;
            if (CompanyMoney < 0)
                // printf("GAMEOVER!!!\n");
                gameOver(0);
        }
    }
}
/*
    订单完成时调用即可
    nowOrder(OrderList *)：目前遍历到的订单，注意，为OrderList指针而非Order指针
*/
void complishOrder(OrderList *nowOrder) // 可以顺便判断是A任务完成还是整个订单完成
{
    OrderList *HeadOrder = AllOrderLog->Nxt_order;
    while (HeadOrder)
    {
        if (HeadOrder->Cur_order->id == nowOrder->Cur_order->id) // 更新全局记录中该订单状态
        {
            if (nowOrder->Cur_order->status == 2) // TODO: 停靠记录
            {
                HeadOrder->Cur_order->status = 3; // 变成已完成
                nowOrder->Cur_order->status = 3;
                nowOrder->Cur_order->end_time = Time;
                HeadOrder->Cur_order->end_time = Time;
                //pop_front_order(nowOrder); // 弹出顶部订单
                CompanyOrderFinish++;
                CompanyMoney += MONEY_GAIN_ONE;
            }
            else if (nowOrder->Cur_order->status == 1)
            {
                HeadOrder->Cur_order->status = 2;
                nowOrder->Cur_order->status = 2; // 更新状态到送单
                nowOrder->Cur_order->end_time = Time;
                HeadOrder->Cur_order->end_time = Time;
                //OrderList *newOrder = nowOrder;
                push_back_order(nowOrder->Cur_order, nowOrder);
                HeadOrder = delete_order(nowOrder);
            }
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
}

/*
    判断订单是否结单
    nowOrder(OrderList *)：目前遍历到的订单，注意，为OrderList指针而非Order指针
    NowRider(Rider *)：目前的骑手，注意，为RiderList指针
 */
int isComplishOrder(OrderList *NowOrder, RiderList *NowRider)
{
    int judge = 0;
    if (NowOrder->Cur_order->status == 1)
        judge = abs((NowOrder->Cur_order->rest_x) - (NowRider->Cur_rider->rider_x)) + abs((NowOrder->Cur_order->rest_y) - (NowRider->Cur_rider->rider_y));
    else if (NowOrder->Cur_order->status == 2)
        judge = abs((NowOrder->Cur_order->cust_x) - (NowRider->Cur_rider->rider_x)) + abs((NowOrder->Cur_order->cust_y) - (NowRider->Cur_rider->rider_y));
    else
        // printf("订单状态错误\n");
        // //exit(0);//终止
        gameOver(3);
    if (judge == 1)
        return 1;
    return 0;
}
/*
    将新订单进行派单
*/
void arrangeNewOrder()
{
    OrderList *newOrder = AllOrderLog->Nxt_order;
    while (newOrder)
    {
        if (newOrder->Cur_order->status == 0)
            getBestRider(newOrder->Cur_order);
        newOrder = newOrder->Nxt_order;
    }
}
