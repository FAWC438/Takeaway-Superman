#include "../Global/header.h"

void push_back(Order * NewOrder,OrderList * List)       //订单入队尾
{
    OrderList * NewOrderList = (OrderList *)malloc(sizeof(OrderList));
    NewOrderList->Cur_order = NewOrder;
    OrderList * BackOrderList = List;
    while(BackOrderList->Nxt_order)
        BackOrderList = BackOrderList->Nxt_order;
    BackOrderList->Nxt_order = NewOrderList;
    NewOrderList->Pre_order = BackOrderList;
    NewOrderList->Nxt_order = NULL;
}

Order * pop_front(OrderList * List)                      //订单出队首
{
    Order * FrontOrder = List->Cur_order;
    List = List->Nxt_order;
    free(List->Pre_order);
    List->Pre_order = NULL;
    return FrontOrder;
}

void swap_order(OrderList * List1,OrderList * List2)    //交换两个订单
{
    Order * TempOrder = List1->Cur_order;
    List1->Cur_order  = List2->Cur_order;
    List2->Cur_order  = TempOrder;
}
