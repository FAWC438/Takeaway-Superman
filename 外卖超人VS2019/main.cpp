
#include "../Global/header.h"
#include <graphics.h>


/*
	文件/控制台输出主程序
*/
void console()
{
	AllOrderLog = creatOrderList(); // 全部订单记录(含有头结点)
	Buffer = creatOrderList();      // 缓冲区(含有头结点)
	AllRiderLog = creatRiderList(); // 全部骑手记录(含有头结点)
	clock_t start_clock, end_clock; // 用于计算程序运行时间
	int flag = 0;
	if (inputFileOrder())
		;
	else
	{
		printf("不存在文件sales.txt!\n");
		printf("1. 从键盘输入\n");
		printf("2. 从鼠标输入\n");
		printf("请输入数字:\n");
		for (;;)
		{
			scanf("%d", &flag);
			if (flag == 1)
			{
				system("cls");
				inputKeyOrder();
				break;
			}
			else if (flag == 2)
			{
				HWND hwnd;
				hwnd = FindWindow("ConsoleWindowClass", NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
				if (hwnd)
					ShowWindow(hwnd, SW_HIDE);				//设置指定窗口的显示状态（关闭控制台）
				mainFunction();
				exit(0);
			}
			else
			{
				printf("输入错误，请重新输入!\n");
				printf("1. 从键盘输入\n");
				printf("2. 从鼠标输入\n");
				printf("请输入数字:\n");
			}
		}
	}

	while (Buffer->Nxt_order || !isAllOrderFinished()) // 结束条件是缓冲区为空
	{
		start_clock = clock();
		Time++;
		//将缓冲区中的订单放到全局订单记录中
		OrderList* tempOrderList = Buffer->Nxt_order;
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
		//招募骑手

		while (CompanyMoney >= 400)
		{
			hireRider();
		}
		//派单之前把骑手背包完成的订单弹出
		initRiderBag();
		//派单算法
		arrangeNewOrder(); // 此处遍历可优化
		//判断是否超时或破产
		isAnyOrderOverTime();
		//骑手移动
		AllRiderMove();
		//判断每一个订单是否完成
		//完成每一个需要完成的订单 但是在骑手背包里不弹出刚完成的订单 （输出文件时判断停靠使用）
		int isAnyOrderComplish = 0;
		RiderList* tempRider = AllRiderLog->Nxt_rider;
		while (tempRider) // 骑手
		{
			OrderList* tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
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
		//有订单完成时，命令行输出刷新一次
		if (isAnyOrderComplish)
		{
			system("cls");
			outputMap();
			outputKey();
		}
		//输出文件
		outputOnFile();
		end_clock = clock();
		// TIME_UNIT * 1000 - (end_clock - start_clock)
		// Sleep(100); // 准确2秒刷新
	}
	gameSuccess();
}

/*
	开始界面
*/
int startScreen()
{
	int x, y, flag = 2;
	int point_one[] = { 340,480,340,400,640,400,640,480 },
		point_two[] = { 340,590,340,510,640,510,640,590 },
		point_three[] = { 340,700,340,620,640,620,640,700 };
	mouse_msg msg = { 0 };

	initgraph(1000, 750);   // 初始化为1000*750大小的窗口
	setcaption("Takeaway Superman");
	setbkcolor(YELLOW);// 背景色
	PIMAGE img;
	img = newimage();
	getimage(img, "final-logo.png", 0, 0);// 背景
	putimage(-100, 0, img);
	setfillcolor(YELLOW);// 方块填充色
	setcolor(YELLOW);// 方块边线色

	/*
		键盘/文件输入按钮
	*/
	// bar(340, 480, 640, 400);
	fillpoly(4, point_one);
	setfont(40, 0, "微软雅黑");
	setcolor(BLACK);// 字体颜色
	outtextrect(395, 420, 640, 380, "键盘/文件输入");

	/*
		鼠标输入按钮
	*/
	setcolor(YELLOW);
	// bar(340, 590, 640, 510);
	fillpoly(4, point_two);
	setfont(40, 0, "微软雅黑");
	setcolor(BLACK);
	outtextrect(430, 530, 640, 490, "鼠标输入");

	/*
		退出按钮
	*/
	setcolor(YELLOW);
	// bar(340, 700, 640, 620);
	fillpoly(4, point_three);
	setfont(40, 0, "微软雅黑");
	setcolor(BLACK);
	outtextrect(460, 640, 640, 500, "退出");
	for (; is_run(); delay_fps(60))
	{

		while (mousemsg())// 获取鼠标消息，这个函数会等待，等待到有消息为止
		{
			msg = getmouse();// 将鼠标信息存入鼠标结构体
		}
		x = msg.x, y = msg.y;
		if (msg.is_left() || msg.is_right())// 左键右键均可
		{
			if (x >= 340 && x <= 640 && y >= 400 && y <= 480)// 键盘/文件输入
			{
				setfillcolor(RED);
				fillpoly(4, point_one);
				floodfillsurface(395, 420, YELLOW);
				flag = 0;
				Sleep(2000);
				break;
			}
			else if (x >= 340 && x <= 640 && y >= 510 && y <= 590)// 鼠标输入
			{
				HWND hwnd;
				hwnd = FindWindow("ConsoleWindowClass", NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
				if (hwnd)
					ShowWindow(hwnd, SW_HIDE);				//设置指定窗口的显示状态（关闭控制台）
				setfillcolor(RED);
				fillpoly(4, point_two);
				floodfillsurface(430, 530, YELLOW);
				flag = 1;
				Sleep(2000);
				break;
			}
			else if (x >= 340 && x <= 640 && y >= 620 && y <= 700)// 退出
			{
				setfillcolor(RED);
				fillpoly(4, point_three);
				floodfillsurface(460, 640, YELLOW);
				flag = 2;
				Sleep(2000);
				break;
			}
			else
				continue;
		}
	}
	delimage(img);
	ege::closegraph();
	return flag;
}

int main()
{
	int flag = 2;
	flag = startScreen();
	if (flag == 0)
		console();// 键盘/文件输入主程序
	else if (flag == 1)
	{
		AllOrderLog = creatOrderList(); // 全部订单记录(含有头结点)
		Buffer = creatOrderList();      // 缓冲区(含有头结点)
		AllRiderLog = creatRiderList(); // 全部骑手记录(含有头结点)
		clock_t start_clock, end_clock; // 用于计算程序运行时间
		mainFunction();// 鼠标输入主程序
	}
	exit(0);
}