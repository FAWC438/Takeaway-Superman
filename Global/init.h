#ifndef _INIT
#define _INIT
#include "header.h"

void initMap()
{
	int i, j;
	for (i = 0; i <= 16; i++)
	{
		for (j = 0; j <= 16; j++)
		{
			if ((i % 2) != (j % 2)) // 初始化道路
			{
				Map[i][j] = 0;
			}
			else
				Map[i][j] = 1; // 初始化房屋
		}
	}
}

/*
	初始化骑手背包，初始化结束时骑手背包都是未完成订单
 */
void initRiderBag()
{
	RiderList *rider = AllRiderLog->Nxt_rider;
	while (rider)
	{
		OrderList *order = rider->Cur_rider->Bag->Nxt_order;
		while (order)
		{
			if (order->Cur_order->status == 3) //把状态为完成的订单删除
				order = delete_order(order);
			order = order->Nxt_order;
		}
		rider = rider->Nxt_rider;
	}
}
#endif
