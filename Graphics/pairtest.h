#include "../Global/header.h"
#include <MMSystem.h>
#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

int mapsignal = 0; // 是否更新骑手动画

HANDLE hMutex1, hMutex2, hMutex3; // 互斥锁

/*
	接收用户鼠标点击操作
	Pair *par：
	int *sum：计数器，用于记录向Buffer输入的订单ID

 */
void clickMap(Pair *par, int *sum)
{
	mouse_msg msg = {0};
	int now_x = -1;
	int now_y = -1;
	if (mousemsg())
	{
		msg = getmouse();
		if (msg.is_left() && msg.is_down())
		{
			now_x = graphXToMapY(msg.x);
			now_y = graphYToMapX(msg.y);
			if (now_x >= 0 && now_x <= 8 && now_y >= 0 && now_y <= 8)
			{
				if (par->is_start && now_y == par->start_x && now_x == par->start_y)
				{
					par->is_start = 0;
				}
				else if (par->is_end && now_y == par->end_x && now_x == par->end_y)
				{
					par->is_end = 0;
				}
				else if (!par->is_start)
				{
					par->is_start = 1;
					par->start_x = now_y;
					par->start_y = now_x;
				}
				else if (!par->is_end)
				{
					par->is_end = 1;
					par->end_x = now_y;
					par->end_y = now_x;
				}
			}
			else if (msg.x >= 700 && msg.y >= 510 && msg.x <= 965 && msg.y <= 595)
			{
				par->is_start = 0;
				par->is_end = 0;
				// 向Buffer内输入
				WaitForSingleObject(hMutex1, INFINITE);
				Order *p = (Order *)malloc(sizeof(Order));
				p->id = *sum;
				(*sum)++;
				p->rest_x = par->start_x * 2;
				p->rest_y = par->start_y * 2;
				p->cust_x = par->end_x * 2;
				p->cust_y = par->end_y * 2;
				p->begin_time = Time + 1;
				p->turn_time = 0x3f3f3f3f;
				p->end_time = 0x3f3f3f3f;
				p->status = 0;
				push_back_order(p, Buffer);
				ReleaseMutex(hMutex1);
			}
			else if (msg.x >= 700 && msg.y >= 605 && msg.x <= 965 && msg.y <= 690)
			{
				if (!CompanyOrderSum)
					exit(0);
				IsEnd = 1;
			}
		}
	}
}

/*
	屏幕右上方的文字输出
 */
void printText()
{
	char s[110];
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfontbkcolor(EGERGB(220, 220, 220));
	setcolor(BLACK);
	setfont(40, 0, "微软雅黑");
	sprintf(s, "时间: %d\n钱: %d\n接单数: %d\n完成数: %d\n超时数: %d", Time, CompanyMoney, CompanyOrderSum, CompanyOrderFinish, CompanyOrderOverTime);
	outtextrect(700, 60, 300, 300, s);
	PIMAGE img[3];
	for (int i = 0; i < 3; i++)
		img[i] = newimage();
	getimage(img[0], "House.png", 0, 0);
	getimage(img[1], "Restaurant.png", 0, 0);
	getimage(img[2], "Dormitory.png", 0, 0);
	putimage(700, 320, img[0]);
	putimage(800, 320, img[1]);
	putimage(900, 320, img[2]);
	setfont(16, 0, "宋体");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	//sprintf(s, "%d", (*sum);
	outtextrect(705, 370, 50, 50, "房屋");
	outtextrect(800, 370, 50, 50, "餐馆(A)");
	outtextrect(900, 370, 50, 50, "宿舍(B)");
	setfont(25, 0, "微软雅黑");
	outtextrect(700, 400, 220, 220, "*房屋轻透明选中餐厅\n*重透明选中宿舍\n*变红表示停靠");
	for (int i = 0; i < 3; i++)
		delimage(img[i]);
}

unsigned __stdcall runGraph(void *cnt_hire)
{
	int *cnt = (int *)cnt_hire;
	int sum = 0; // 记录总输入数量，便于编写ID
	Pair par;
	int countTime = 0;
	initgraph(1000, 750);
	createGraph();
	for (; is_run(); delay_fps(160))
	{
		createMap(par, &sum);
		clickMap(&par, &sum);
		createRoad();
		if (IsEnd == 2)
		{
			gameSuccessG();
			break;
		}
		else if (IsEnd == 3)
		{
			gameOverG();
			break;
		}
		else if (IsEnd == 4)
		{
			gameOverG();
			break;
		}
		printText();
		if (mapsignal)
		{
			drawRider(&countTime, cnt);
			mapsignal = 0;
			countTime = 0;
		}
		else
			drawRider(&countTime, cnt);
		countTime++;
	}
	getch();
	_endthreadex(0);
	return 0;
}

/*
	鼠标输入，动画输出的主函数
 */
void mainFunction()
{
	PlaySound("11303.wav", NULL, SND_LOOP | SND_ASYNC);
	int cnt_hire = 0; // 记录每次招募骑手数量
	updateMap();
	HANDLE hThread;
	clock_t start_clock, end_clock; // 用于计算程序运行时间
	//initMap();
	unsigned int ThreadID = 1;
	hThread = (HANDLE)_beginthreadex(NULL, 0, runGraph, (void *)&cnt_hire, 0, &ThreadID);
	hMutex1 = CreateMutex(NULL, FALSE, NULL);
	//while (Buffer->Nxt_order || !isAllOrderFinished()) // 结束条件是缓冲区为空
	while (!(IsEnd == 1 && isAllOrderFinished()))
	{
		cnt_hire = 0;
		start_clock = clock();
		Time++;
		//将缓冲区中的订单放到全局订单记录中
		WaitForSingleObject(hMutex1, INFINITE);
		OrderList *tempOrderList = Buffer->Nxt_order;
		while (tempOrderList)
		{
			if (tempOrderList->Cur_order->begin_time == Time)
			{
				push_back_order(tempOrderList->Cur_order, AllOrderLog);
				tempOrderList = delete_order(tempOrderList);
				CompanyOrderSum++; // 公司的总订单+1
			}
			tempOrderList = tempOrderList->Nxt_order;
		}
		ReleaseMutex(hMutex1);
		//招募骑手
		while (CompanyMoney >= 400)
		{
			hireRider();
			cnt_hire++;
		}
		//派单之前把骑手背包完成的订单弹出
		initRiderBag();
		//派单算法
		arrangeNewOrder(); // 此处遍历可优化
		//判断是否超时或破产
		isAnyOrderOverTime();
		if (IsEnd == 3 || IsEnd == 4)
		{
			break;
		}
		//骑手移动
		AllRiderMove();
		mapsignal = 1;
		//判断每一个订单是否完成
		//完成每一个需要完成的订单 但是在骑手背包里不弹出刚完成的订单 （输出文件时判断停靠使用）
		end_clock = clock();
		api_sleep(TIME_UNIT * 1500 - (end_clock - start_clock)); // 准确2秒刷新
		start_clock = clock();
		int isAnyOrderComplish = 0;
		RiderList *tempRider = AllRiderLog->Nxt_rider;
		while (tempRider) // 骑手
		{
			OrderList *tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
			while (tempOrder) // 背包
			{
				if (isComplishOrder(tempOrder, tempRider))
				{
					tempOrder = complishOrder(tempOrder);
					isAnyOrderComplish = 1;
				}
				tempOrder = tempOrder->Nxt_order;
			}
			tempRider = tempRider->Nxt_rider;
		}
		updateMap();
		////end_clock = clock();
		// TIME_UNIT * 1000 - (end_clock - start_clock)
	}
	if (!(IsEnd == 3 || IsEnd == 4))
		IsEnd = 2;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	closegraph(); // 关闭图形界面
}