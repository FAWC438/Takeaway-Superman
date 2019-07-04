#include "./Global/header.h"

void swap_order(OrderList *List1, OrderList *List2) //交换两个订单
{
    Order *TempOrder = List1->Cur_order;
    List1->Cur_order = List2->Cur_order;
    List2->Cur_order = TempOrder;
}