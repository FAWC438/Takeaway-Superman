#include "../Global/header.h"
/*
	从文件输入
 */
int inputFileOrder() // TODO: 处理输入数据和要计算的数据的关系
{
	Order *p = (Order *)malloc(sizeof(Order));
	FILE *fp = fopen("sales.txt", "r"); // 打开文件
	if (fp == NULL)
	{
		free(p);
		return 0;
	}
	while ((fscanf(fp, "%d %d %d %d %d %d\n", &p->id, &p->begin_time,
				   &p->rest_x, &p->rest_y,
				   &p->cust_x, &p->cust_y)) != EOF)
	{
		p->status = 0;									// 未接单状态
		p->turn_time = 0x3f3f3f3f;
		p->end_time = 0x3f3f3f3f;						// 破产时间
		//p->warn_time = p->begin_time + FINE_FIRST_TIME; // 罚款时间
		push_back_order(p, Buffer);						// 添加到全局订单记录后
		p = (Order *)malloc(sizeof(Order));				// 给p新的空间
	}
	free(p); // 释放p的内存
	return 1;
}

/*
	从键盘输入
 */
void inputKeyOrder()
{
	Order *p = (Order *)malloc(sizeof(Order));
	while (scanf_s("%d %d %d %d %d %d\n", &p->id, &p->begin_time,
				   &p->rest_x, &p->rest_y,
				   &p->cust_x, &p->cust_y) != EOF)
	{
		p->status = 0;									// 未接单状态
		p->turn_time = 0x3f3f3f3f;
		p->end_time = 0x3f3f3f3f;						// 破产时间
		//p->warn_time = p->begin_time + FINE_FIRST_TIME; // 罚款时间
		push_back_order(p, Buffer);						// 添加到全局订单记录后
		p = (Order *)malloc(sizeof(Order));				// 给p新的空间
	}
	free(p); // 释放p的内存
}
