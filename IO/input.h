#include "../Global/header.h"
/*
	从文件输入
 */
int inputFileOrder() // TODO: 处理输入数据和要计算的数据的关系
{
	//if (_access("D:/code/cpp/小学期计导/大作业/Takeaway-Superman/sales.txt", 0) == -1)
	//{
	//	// 判断是否存在文件，不存在则返回0
	//	return 0;
	//}
	Order* p = (Order*)malloc(sizeof(Order));
	FILE* fp = fopen("C:/Code/Project/Takeaway-Superman/sales.txt", "r"); // 打开文件
	if (fp == NULL)
	{
		free(p);
		return 0;
	}
	while ((fscanf(fp, "%d %d %d %d %d %d\n", &p->id, &p->begin_time,
		&p->rest_x, &p->rest_y,
		&p->cust_x, &p->cust_y)) != EOF)
	{
		p->status = 0;                                  // 未接单状态
		p->end_time = 0x3f3f3f3f; // 破产时间
		p->warn_time = p->begin_time + FINE_FIRST_TIME; // 罚款时间
		push_back_order(p, Buffer);                     // 添加到全局订单记录后
		p = (Order*)malloc(sizeof(Order));             // 给p新的空间
	}
	free(p); // 释放p的内存
	fclose(fp);
	return 1;
}

/*
	从键盘输入
 */
int inputKeyOrder()
{
	Order* p = (Order*)malloc(sizeof(Order));
	while (scanf_s("%d %d %d %d %d %d\n", &p->id, &p->begin_time,
		&p->rest_x, &p->rest_y,
		&p->cust_x, &p->cust_y) != EOF)
	{
		p->status = 0;                                  // 未接单状态
		p->end_time = 0x3f3f3f3f; // 破产时间
		p->warn_time = p->begin_time + FINE_FIRST_TIME; // 罚款时间
		push_back_order(p, Buffer);                     // 添加到全局订单记录后
		p = (Order*)malloc(sizeof(Order));             // 给p新的空间
	}
	free(p); // 释放p的内存
	return 1;
}
