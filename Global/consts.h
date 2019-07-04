
/*
    变量与常量
*/

#ifndef _VARIABLE
#define _VARIABLE
#include "header.h"

const int TIME_UNIT = 2;         // 时间单位为TIME_UNIT秒
const int INIT_MONEY = 1000;     // 起始资金
const int HIRE_MONEY = 300;      // 招募一个人需要的资金
const int DEAD_TIME = 3;         // 超过DEAD_TIME时间单位后，被视为拒单
const int FINE_FIRST_TIME = 30;  // 超时时间，第一次超时罚款
const int FINE_MONEY = 50;       // 第一次超时罚款金额
const int FINE_SECOND_TIME = 60; // 超时时间，第二次超时倒闭
const int MONEY_GAIN_ONE = 10;   // 完成一单获得的钱
const int MAP_X = 17;            // 地图X大小
const int MAP_Y = 17;            // 地图Y大小

/*
    公司状态变量
    为区分全局常量，全局变量命名如下所示
 */
int CompanyMoney = 1000;     // 当前公司有多少钱
int CompanyRiderCount = 0;   // 公司骑手数量
int Time = 0;                // 当前时间，即Time个时间单位
int CompanyOrderSum = 0;      // 公司接单数
int CompanyOrderFinish = 0;   // 公司完成数
int CompanyOrderOverTime = 0; // 公司超时单数

OrderList *AllOrderLog; // 全部订单记录
RiderList *AllRiderLog; // 全部骑手记录

#endif