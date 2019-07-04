#include <./Global/header.h>

int inputKeyOrder()
{
    Order *p = (Order *)malloc(sizeof(Order));
    while (scanf("%d %d %d %d %d %d\n", &p->id, &p->begin_time,
                 &p->rest_x, &p->rest_y,
                 &p->cust_x, &p->cust_y))
    {
        p->status = 0;
        p->end_time = p->begin_time + FINE_SECOND_TIME;
        p->warn_time = p->begin_time + FINE_FIRST_TIME;
        CompanyOrderSum++;
        push_back(p, AllOrderLog);          // 添加到全局订单记录后
        p = (Order *)malloc(sizeof(Order)); // 给p新的空间
    }
    free(p); // 释放p的内存
    return 1;
}