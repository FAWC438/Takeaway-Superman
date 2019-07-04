<<<<<<< HEAD
#ifndef _INPUTBYFILE
#define _INPUTBYFILE
#include "../Global/header.h"
=======
#include "./Global/header.h"
>>>>>>> 690a1b9b7071ecb76883829fa0fe8816c4c9a01d

int inputFileOrder()
{
    if (access("sales.txt", 0) == -1)
    {
        // 判断是否存在文件，不存在则返回0
        return 0;
    }
    Order *p = (Order *)malloc(sizeof(Order));
    FILE *fp = fopen("sales.txt", "r"); // 打开文件
    while (fscanf(fp, "%d %d %d %d %d %d\n", &p->id, &p->begin_time,
                  &p->rest_x, &p->rest_y,
                  &p->cust_x, &p->cust_y))
    {
        p->status = 0;
        p->end_time = p->begin_time + FINE_SECOND_TIME;
        p->warn_time = p->begin_time + FINE_FIRST_TIME;
        CompanyOrderSum++;
<<<<<<< HEAD
        push_back(p, AllOrderLog);
=======
        push_back(p, AllOrderLog);          // 添加到全局订单记录后
        p = (Order *)malloc(sizeof(Order)); // 给p新的空间
>>>>>>> 690a1b9b7071ecb76883829fa0fe8816c4c9a01d
    }
    free(p); // 释放p的内存
    return 1;
}
#endif
