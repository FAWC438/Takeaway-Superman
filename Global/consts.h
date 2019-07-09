
/*
    变量与常量
*/

#ifndef _VARIABLE
#define _VARIABLE
#include "header.h"

const int TIME_UNIT = 2;         // 时间单位为TIME_UNIT秒
const int INIT_MONEY = 100;     // 起始资金
const int HIRE_MONEY = 300;      // 招募一个人需要的资金
const int DEAD_TIME = 3;         // 超过DEAD_TIME时间单位后，被视为拒单
const int FINE_FIRST_TIME = 30;  // 超时时间，第一次超时罚款
const int FINE_MONEY = 50;       // 第一次超时罚款金额
const int FINE_SECOND_TIME = 60; // 超时时间，第二次超时倒闭
const int MONEY_GAIN_ONE = 10;   // 完成一单获得的钱
const int MAP_X = 17;            // 地图X大小
const int MAP_Y = 17;            // 地图Y大小
const int COMPANY_X = 7;         //公司所在X大小
const int COMPANY_Y = 8;         //公司所在Y大小

/*
    公司状态变量
    为区分全局常量，全局变量命名如下所示
 */
int CompanyMoney = INIT_MONEY;      // 当前公司有多少钱
int CompanyRiderCount = 0;    // 公司骑手数量
int Time = -1;                // 当前时间，即Time个时间单位
int CompanyOrderSum = 0;      // 公司接单数
int CompanyOrderFinish = 0;   // 公司完成单数
int CompanyOrderOverTime = 0; // 公司超时单数

OrderList *AllOrderLog; // 全部订单记录(含有头结点)
OrderList *Buffer;      // 缓冲区(含有头结点)
RiderList *AllRiderLog; // 全部骑手记录(含有头结点)
int Map[17][17];        // 输出用，0为道路，1为普通房屋，2为餐厅，3为宿舍，4为骑手

#endif