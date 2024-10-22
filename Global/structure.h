
/*
	全局结构体
	注意：本项目所有链表都具有空头结点！！！
 */

#ifndef _STRUCTURE
#define _STRUCTURE

#include "header.h"

typedef struct _Order // 订单
{
	int id;				// 订单ID
	int begin_time;		// 起始时间戳
	int turn_time;		// A任务转B任务时间戳
	int end_time;		// 截止时间戳
	int rest_x, rest_y; // 餐厅位置
	int cust_x, cust_y; // 顾客位置
	int status;			// 订单状态 0未接单，1取餐，2送餐，3完成
} Order;

typedef struct _OrderList // 订单链表
{
	struct _OrderList *Pre_order; // 上一个订单
	struct _OrderList *Nxt_order; // 下一个订单
	Order *Cur_order;			  // 当前订单
} OrderList;

typedef struct _Rider // 骑手
{
	int id;				  // 骑手ID
	int rider_x, rider_y; // 骑手当前位置
	OrderList *Bag;		  // 骑手背包订单
	int path_mode;		  // 骑手动画移动模式
} Rider;

typedef struct _RiderList // 骑手列表(便于遍历)
{
	struct _RiderList *Pre_rider; // 上一个骑手
	struct _RiderList *Nxt_rider; // 下一个骑手
	Rider *Cur_rider;			  // 当前骑手
} RiderList;

typedef struct _Pair // 储存鼠标输入信息
{
	int start_x, start_y;		  // 餐厅位置
	int end_x, end_y;			  // 宿舍位置
	int is_start = 0, is_end = 0; // 是否选定餐厅；是否选定宿舍
} Pair;

#endif