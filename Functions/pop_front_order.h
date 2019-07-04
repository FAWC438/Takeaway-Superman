#include "../Global/header.h"
/*
    删除头部订单
 */
Order *pop_front_order(OrderList *List) //订单出队首
{
    Order *FrontOrder = List->Cur_order;
    List = List->Nxt_order;
    free(List->Pre_order);
    List->Pre_order = NULL;
    return FrontOrder;
}