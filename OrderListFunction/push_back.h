#include "./Global/header.h"

void push_back_order(Order *NewOrder, OrderList *List) //订单入队尾
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