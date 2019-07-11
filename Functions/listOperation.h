#include "../Global/header.h"

/*
	传入链表，删除头部订单
	List：订单链表
 */
void pop_front_order(OrderList *List)
{
	OrderList *p = List->Nxt_order;
	List->Nxt_order = List->Nxt_order->Nxt_order;
	List->Nxt_order->Pre_order = List;
	free(p);
}
/*
	添加尾部订单
	NewOrder：添加的订单
	List：订单列表
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
	NewRider：新的骑手
	List：骑手列表
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
/*
	删除订单，返回该订单的前一个订单
	tOrder：目标订单
 */
OrderList *delete_order(OrderList *tOrder)
{
	OrderList *tempOrder = tOrder->Pre_order;
	tOrder->Pre_order->Nxt_order = tOrder->Nxt_order;
	if (tOrder->Nxt_order) //如果后驱结点存在，改变后驱结点的前一个结点的指向
		tOrder->Nxt_order->Pre_order = tOrder->Pre_order;
	free(tOrder);
	return tempOrder;
}