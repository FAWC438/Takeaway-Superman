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

int predRiderPath(Rider *nowRider)
{
	int pos_x = -1, pos_y = -1;
	int cur_x, cur_y;
	if (nowRider->Bag->Nxt_order && nowRider->Bag->Nxt_order->Cur_order->status == 1) //找到pos_x，pos_y，策略是优先送包里第一个订单;
	{
		pos_x = nowRider->Bag->Nxt_order->Cur_order->rest_x;
		pos_y = nowRider->Bag->Nxt_order->Cur_order->rest_y;
	}
	else if (nowRider->Bag->Nxt_order && nowRider->Bag->Nxt_order->Cur_order->status == 2)
	{
		pos_x = nowRider->Bag->Nxt_order->Cur_order->cust_x;
		pos_y = nowRider->Bag->Nxt_order->Cur_order->cust_y;
	}
	cur_y = nowRider->rider_y;
	cur_x = nowRider->rider_x;
	// 停止状态
	if (pos_x == -1 && pos_y == -1)
		return 6;
	// 先左右
	else if (cur_y < pos_y - 1 || cur_y > pos_y + 1)
	{
		if (cur_x % 2 == 1 && cur_y % 2 == 0) // 在横向道路上
		{
			if (cur_y > pos_y + 1)		// 在右边就要往左走
				return 3;				//左
			else if (cur_y < pos_y - 1) // 在左边要往右走
				return 0;				//右
		}
		else if (cur_x % 2 == 0 && cur_y % 2 == 1) // 在纵向道路上
		{
			if (cur_y > pos_y + 1) // 在右边就要往左走
			{
				if (pos_x >= cur_x || (pos_x == cur_x && pos_x == 0)) // 目标在下或同行
					return 4;										  //左下
				else												  // 目标在上
					return 1;										  //左上
			}
			else if (cur_y < pos_y + 1) // 在右边就要往左走
			{
				if (pos_x > cur_x || (pos_x == cur_x && pos_x == 0)) // 目标在下或同行
					return 5;										 //右下
				else												 // 目标在上
					return 2;										 //右上
			}
		}
	}
	// 后上下
	else if (cur_x < pos_x - 1 || cur_x > pos_x + 1)
	{
		if (cur_x % 2 == 0 && cur_y % 2 == 1) // 在纵向道路上
		{
			if (cur_x > pos_x + 1)		// 在下边就要往上走
				return 0;				//上
			else if (cur_x < pos_x - 1) // 在上边要往下走
				return 3;				//下
		}
		else if (cur_x % 2 == 1 && cur_y % 2 == 0) // 在横向道路上
		{
			if (cur_x > pos_x + 1) // 在下边就要往上走
			{
				if (pos_y > cur_y || (pos_y == cur_y && pos_y == 0)) // 目标在右或同列
					return 1;										 //右上
				else												 // 目标在左
					return 4;										 //左上
			}
			if (cur_x < pos_x + 1) // 在上边就要往下走
			{
				if (pos_y > cur_y || (pos_y == cur_y && pos_y == 0)) // 目标在右或同列
					return 2;										 //右下
				else												 // 目标在左
					return 5;										 //左下
			}
		}
	}
}

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
		if (HeadOrder->Cur_order->status == 2 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // 停靠餐厅
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3;
		}
		else if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2;  // 餐厅地图更新
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3; // 停靠宿舍
		}
		else if ((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3) || (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time))
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
