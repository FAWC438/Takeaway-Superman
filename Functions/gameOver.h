#include "./Global/header.h"
/*
    破产结算函数
*/

/* 
    破产结算
    以下列出调用该函数的情况(int reason)：
    0. 破产：资金为负数
    1. 拒单：超过DEAD_TIME个时间单位接单
    2. 恶意拖单：第二次超时，即接单后，在FINE_SECOND_TIME时间单位内未送达
    3. 订单状态错误
    4. 输入格式错误
    5. 程序运行异常（eg. 咋骑手跑到房子里了？）
*/
void gameOver(int reason)
{
    printf("------------------------------------------------\n");
    printf("公司已经破产！！！\n");
    printf("公司破产原因：");
    if (reason == 0)
        printf("破产\n");
    else if (reason == 1)
        printf("拒单\n");
    else if (reason == 2)
        printf("恶意废单\n");
    else
        printf("异常原因，错误代码为%d\n", reason);
    printf("本次公司所在地址:（%d，%d）\n", COMPANY_X, COMPANY_Y);
    printf("公司剩余现金数：%d\n", CompanyMoney);
    printf("公司骑手数量：%d\n", CompanyRiderCount);
    printf("公司收益利润：%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
    printf("破产时间：%d个时间单位\n", Time);
    printf("公司接单数：%d\n", CompanyOrderSum);
    printf("公司完成单数:%d\n", CompanyOrderFinish);
    printf("公司超时单数:%d\n", CompanyOrderOverTime);

    // 释放全局变量内存
    OrderList *p1 = AllOrderLog;
    RiderList *p2 = AllRiderLog;
    // 释放AllOrderLog
    while (p1)
    {
        free(p1->Pre_order);
        free(p1->Cur_order);
        p1->Pre_order = NULL;
        p1->Cur_order = NULL;
        p1 = p1->Nxt_order;
    }
    // 释放AllRiderLog
    while (p2)
    {
        free(p2->Pre_order);
        free(p2->Cur_rider->Bag);
        p2->Cur_rider->Bag = NULL;
        free(p2->Cur_rider);
        p2->Pre_order = NULL;
        p2->Cur_order = NULL;
        p2 = p2->Nxt_order;
    }
    printf("GAME OVER!!!\n");
    system("PAUSE");
    exit(0);
}

/* 
    正常结算
    以下列出调用该函数的情况：
    1. 鼠标操作手动结束游戏
*/

void gameSuccess()
{
    printf("------------------------------------------------\n");
    printf("公司存活到了最后！！！You are the true Takeaway Superman！\n");
    printf("本次公司所在地址:（%d，%d）\n", COMPANY_X, COMPANY_Y);
    printf("公司剩余现金数：%d\n", CompanyMoney);
    printf("公司骑手数量：%d\n", CompanyRiderCount);
    printf("公司收益利润：%d\n", CompanyMoney + CompanyRiderCount * HIRE_MONEY - INIT_MONEY);
    printf("破产时间：%d个时间单位\n", Time);
    printf("公司接单数：%d\n", CompanyOrderSum);
    printf("公司完成单数:%d\n", CompanyOrderFinish);
    printf("公司超时单数:%d\n", CompanyOrderOverTime);

    // 释放全局变量内存
    OrderList *p1 = AllOrderLog;
    RiderList *p2 = AllRiderLog;
    // 释放AllOrderLog
    while (p1)
    {
        free(p1->Pre_order);
        free(p1->Cur_order);
        p1->Pre_order = NULL;
        p1->Cur_order = NULL;
        p1 = p1->Nxt_order;
    }
    // 释放AllRiderLog
    while (p2)
    {
        free(p2->Pre_order);
        free(p2->Cur_rider->Bag);
        p2->Cur_rider->Bag = NULL;
        free(p2->Cur_rider);
        p2->Pre_order = NULL;
        p2->Cur_order = NULL;
        p2 = p2->Nxt_order;
    }
    printf("GAME SUCCESS!!!\n");
    system("PAUSE");
    exit(0);
}

/*
    TODO:
    异常结算
    以下列出调用该函数的情况（return值）
    0. 输入异常：未按照正常格式输入
    1. 骑手移动异常：骑手位置未在道路上方
    2. ...
 */