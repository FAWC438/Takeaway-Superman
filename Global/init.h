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
	初始化图形界面地图
*/
void updateMap()
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

	// 初始化房屋类型
	OrderList *HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	while (HeadOrder)
	{
		if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->turn_time == Time && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // 停靠餐厅
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3;
		}
		else if (HeadOrder->Cur_order->status == 2 && HeadOrder->Cur_order->turn_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // 餐厅地图更新
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3;  // 停靠宿舍
		}
		else if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2;  // 餐厅地图更新
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3; // 停靠宿舍
		}
		else if ((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3))
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2; // 餐厅地图更新
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3; // 宿舍地图更新
		}
		HeadOrder = HeadOrder->Nxt_order;
	}
	// 初始化骑手位置
	RiderList *HeadRider = AllRiderLog;
	HeadRider = HeadRider->Nxt_rider;
	while (HeadRider)
	{
		//if (HeadRider->Cur_rider->Bag->Nxt_order)
		Map[HeadRider->Cur_rider->rider_x][HeadRider->Cur_rider->rider_y] = 4; // 骑手地图更新
		//HeadRider->Cur_rider->path_mode = predRiderPath(HeadRider->Cur_rider);
		HeadRider = HeadRider->Nxt_rider;
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
