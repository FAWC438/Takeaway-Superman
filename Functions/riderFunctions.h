#include "./Global/header.h"

int hireRider() // 招募骑手,返回骑手的id，注意，前提条件是CompanyMoney>=400
{
    CompanyMoney -= 300;
    RiderList *p = AllRiderLog;
    Rider *newRider = (Rider *)malloc(sizeof(Rider));

    while (p->Nxt_rider)
    {
        p = p->Nxt_rider;
    }
    // 初始化新骑手
    newRider->Cur_order = NULL;
    newRider->id = p->Cur_rider->id + 1;
    newRider->rider_x = COMPANY_X;
    newRider->rider_y = COMPANY_Y;
}