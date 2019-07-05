#include "../Global/header.h"

/*
    删除头部订单
 */
Order *pop_front_order(OrderList *List)
{
    Order *FrontOrder = List->Nxt_order->Cur_order;
    List = List->Nxt_order;
    free(List->Pre_order);
    List->Pre_order = NULL;
    List->Cur_order = NULL;
    return FrontOrder;
}
/*
    添加尾部订单
 */
void push_back_order(Order *NewOrder, OrderList *List)
{
    OrderList *NewOrderList = (OrderList *)malloc(sizeof(OrderList));
    NewOrderList->Cur_order = NewOrder;
    OrderList *BackOrderList = List;
    while (BackOrderList->Nxt_order)
        BackOrderList = BackOrderList->Nxt_order;
    BackOrderList->Nxt_order = NewOrderList;
    NewOrderList->Pre_order = BackOrderList;
    NewOrderList->Nxt_order = NULL;
}
/*
    骑手队列尾部添加骑手
 */
void push_back_rider(Rider *NewRider, RiderList *List)
{
    RiderList *NewRiderList = (RiderList *)malloc(sizeof(RiderList));
    NewRiderList->Cur_rider = NewRider;
    RiderList *BackRiderList = List;
    while (BackRiderList->Nxt_rider)
        BackRiderList = BackRiderList->Nxt_rider;
    BackRiderList->Nxt_rider = NewRiderList;
    NewRiderList->Pre_rider = BackRiderList;
    NewRiderList->Nxt_rider = NULL;
}
/*
    订单列表交换
 */
void swap_order(OrderList *List1, OrderList *List2)
{
    Order *TempOrder = List1->Cur_order;
    List1->Cur_order = List2->Cur_order;
    List2->Cur_order = TempOrder;
}