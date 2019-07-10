#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <windows.h>
using namespace std;

extern int Map[17][17];

const int HWID = 50;
const int RWID = 25;

struct Pair
{
	int start_x, start_y;
	int end_x, end_y;
	int is_start, is_end;
};

void createGraph()
{
	// 背景
	setbkcolor(EGERGB(238, 233, 233));
	// 模块
	setfillcolor(LIGHTGRAY);
	bar(25, 50, 675, 700);
	setfillcolor(EGERGB(220, 220, 220));
	bar(690, 50, 975, 485);
	setfillcolor(EGERGB(176, 196, 222));
	bar(690, 510, 975, 595);
	setfillcolor(EGERGB(233, 150, 122));
	bar(690, 615, 975, 700);
	// 按钮及文字
	setfontbkcolor(EGERGB(176, 196, 222));
	setcolor(EGERGB(119, 136, 153));
	setfont(50, 0, "黑体");
	outtextxy(770, 530, "确定");
	setfontbkcolor(EGERGB(233, 150, 122));
	outtextxy(770, 635, "退出");
}

void createMap(Pair par)
{
	PIMAGE img[6];
	for (int i = 1; i <= 3; i++)
		img[i] = newimage();
	getimage(img[1], "House.png", 0, 0);
	getimage(img[2], "Restaurant.png", 0, 0);
	getimage(img[3], "Dormitory.png", 0, 0);
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if ((par.is_start && par.start_x == i && par.start_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x80);
			}
			else if ((par.is_end && par.end_x == i && par.end_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x20);
			}
			else
				putimage_transparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
		}
	//	if(sub_cnt)
	//	{
	//		sub_cnt = 0;
	//	}
	for (int i = 1; i <= 3; i++)
		delimage(img[i]);
}
// 地图中的x坐标转成输出画面的左上角y坐标
int mapXToGraphY(int now_x)
{
	now_x /= 2;
	return (HWID + (HWID + RWID) * now_x);
}
// 地图中的y坐标转成输出画面的左上角x坐标
int mapYToGraphX(int now_y)
{
	now_y /= 2;
	return (RWID + (HWID + RWID) * now_y);
}
// 画面x坐标转换为地图y坐标
int graphXToMapY(int now_x)
{
	now_x -= RWID;
	now_x /= (HWID + RWID);
	return now_x;
}
// 画面y坐标转换为地图x坐标
int graphYToMapX(int now_y)
{
	now_y -= HWID;
	now_y /= (HWID + RWID);
	return now_y;
}

void clickMap(Pair *par)
{
	mouse_msg msg = {0};
	int now_x = -1;
	int now_y = -1;
	int sub_cnt = 0;
	int ext_cnt = 0;
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
				sub_cnt = 1;
				// TODO: 输入
			}
			else if (msg.x >= 700 && msg.y >= 605 && msg.x <= 965 && msg.y <= 690)
			{
				// TODO: 结算
				exit(0);
			}
		}
	}
}

void mainFunction()
{
	Pair par;
	for (int i = 0; i <= 16; i++)
		for (int j = 0; j <= 16; j++)
			Map[i][j] = 1;
	Map[4][4] = 2;
	Map[8][10] = 3;
	initgraph(1000, 750);
	createGraph();

	for (; is_run(); delay_fps(120))
	{
		clickMap(&par);
		createMap(par);
	}
	closegraph(); // 关闭图形界面
}
