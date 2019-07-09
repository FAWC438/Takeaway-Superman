#include "../Global/header.h"

/*
	每次刷新时间点后判断是否有超时订单，若破产则结束游戏
*/
void isAnyOrderOverTime()
{
	OrderList* HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	while (HeadOrder)
	{
		if (HeadOrder->Cur_order->status == 3)
		{
			HeadOrder = HeadOrder->Nxt_order;
			continue;
		}// 不处理已完成订单

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
		HeadOrder = HeadOrder->Nxt_order;
	}
}
/*
	订单完成时调用即可
	nowOrder(OrderList *)：目前遍历到的订单，注意，为OrderList指针而非Order指针
*/
OrderList* complishOrder(OrderList* nowOrder) // 可以顺便判断是A任务完成还是整个订单完成
{
	OrderList* HeadOrder = AllOrderLog->Nxt_order;
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
				return nowOrder;
			}
			else if (nowOrder->Cur_order->status == 1)
			{
				HeadOrder->Cur_order->status = 2;
				nowOrder->Cur_order->status = 2; // 更新状态到送单
				nowOrder->Cur_order->end_time = Time;
				HeadOrder->Cur_order->end_time = Time;
				//OrderList *newOrder = nowOrder;
				Order* tOrder = nowOrder->Cur_order;
				push_back_order(tOrder, nowOrder);
				return delete_order(nowOrder);
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
int isComplishOrder(OrderList* NowOrder, RiderList* NowRider)
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
	OrderList* newOrder = AllOrderLog->Nxt_order;
	while (newOrder)
	{
		if (newOrder->Cur_order->status == 0)
			getBestRider(newOrder->Cur_order);
		newOrder = newOrder->Nxt_order;
	}
}
