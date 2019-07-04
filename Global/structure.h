
/*
    全局结构体
 */

#ifndef _STRUCTURE
#define _STRUCTURE

#include "header.h"

typedef struct _Order // 订单
{
    int id;             // 订单ID
    int begin_time;     // 起始时间戳
    int warn_time;      // 超时时间戳
    int end_time;       // 截止时间戳
    int rest_x, rest_y; // 餐厅位置
    int cust_x, cust_y; // 顾客位置
    int status;         // 订单状态 0未接单，1取餐，2送餐，3完成
} Order;

typedef struct _OrderList // 订单链表
{
    struct _OrderList *Pre_order; // 上一个订单
    struct _OrderList *Nxt_order; // 下一个订单
    Order *Cur_order;             // 当前订单
} OrderList;

typedef struct _Rider // 骑手
{
    int id;               // 骑手ID
    int rider_x, rider_y; // 骑手当前位置
    OrderList *Bag;       // 骑手背包订单
    //Order *Cur_order;     // 骑手当前订单
} Rider;

typedef struct _RiderList // 骑手列表(便于遍历)
{
    struct _RiderList *Pre_rider; // 上一个骑手
    struct _RiderList *Nxt_rider; // 下一个骑手
    Rider *Cur_rider;             // 当前骑手
} RiderList;

#endif