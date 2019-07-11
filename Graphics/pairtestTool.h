#include "../Global/header.h"

/*
	基本图像建立
 */
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

/*
	建立地图
 */
void createMap(Pair par, int *sum)
{
	PIMAGE img[7];
	for (int i = 1; i <= 6; i++)
		img[i] = newimage();
	getimage(img[1], "House.png", 0, 0);
	getimage(img[2], "Restaurant.png", 0, 0);
	getimage(img[3], "Dormitory.png", 0, 0);
	getimage(img[4], "House1.png", 0, 0);
	getimage(img[5], "Restaurant1.png", 0, 0);
	getimage(img[6], "Dormitory1.png", 0, 0);
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if ((par.is_start && par.start_x == i && par.start_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[abs(Map[i * 2][j * 2])], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x80);
				char s[11];
				setfont(30, 0, "微软雅黑");
				setcolor(BLACK);
				setbkmode(TRANSPARENT);
				sprintf(s, "%d", (*sum) + 1);
				outtextrect(RWID + (HWID + RWID) * j + 20, HWID + (HWID + RWID) * i + 10, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i, s);
			}
			else if ((par.is_end && par.end_x == i && par.end_y == j))
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_alphatransparent(NULL, img[abs(Map[i * 2][j * 2])], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK, 0x20);
				char s[11];
				setfont(30, 0, "微软雅黑");
				setcolor(BLACK);
				setbkmode(TRANSPARENT);
				sprintf(s, "%d", (*sum) + 1);
				outtextrect(RWID + (HWID + RWID) * j + 20, HWID + (HWID + RWID) * i + 10, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i, s);
			}
			else if (Map[i * 2][j * 2] < 0) // 停靠
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_transparent(NULL, img[-Map[i * 2][j * 2] + 3], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
			}
			else
			{
				setfillcolor(LIGHTGRAY);
				bar(RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, HWID + RWID + (HWID + RWID) * j, 2 * HWID + (HWID + RWID) * i);
				putimage_transparent(NULL, img[Map[i * 2][j * 2]], RWID + (HWID + RWID) * j, HWID + (HWID + RWID) * i, BLACK);
			}
		}
	for (int i = 1; i <= 6; i++)
		delimage(img[i]);
}

/*
	建立道路的图像
 */
void createRoad()
{
	//声明一个img图片对象
	PIMAGE img[3];
	//建立对象
	for (int i = 0; i < 3; i++)
		img[i] = newimage();
	getimage(img[0], "十字路口.png", 25, 25);
	getimage(img[1], "横向道路.png", 25, 25);
	getimage(img[2], "纵向道路.png", 25, 25);

	setbkcolor(DARKGRAY);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			setviewport(25, 50, 675, 700, 0);
			if (i % 2 == 1 && j % 2 == 0) //横向道路
			{
				putimage(j / 2 * (HWID + RWID), (i - 1) / 2 * (HWID + RWID) + HWID, img[1]);
				putimage(j / 2 * (HWID + RWID) + RWID, (i - 1) / 2 * (HWID + RWID) + HWID, img[1]);
			}
			else if (i % 2 == 0 && j % 2 == 1) //纵向道路
			{
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, i / 2 * (HWID + RWID), img[2]);
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, i / 2 * (HWID + RWID) + RWID, img[2]);
			}
			else if (i % 2 == 1 && j % 2 == 1) //十字路口
			{
				putimage((j - 1) / 2 * (HWID + RWID) + HWID, (i - 1) / 2 * (HWID + RWID) + HWID, img[0]);
			}
		}
	}
	setviewport(0, 0, 1000, 750, 0);
	//释放对象
	for (int i = 0; i < 3; i++)
		delimage(img[i]);
}

/*
	绘制骑手，并控制骑手移动
 */
void drawRider(int *countTime, int *cnt_hire)
{
	PIMAGE rider_img = newimage();

	RiderList *nowRider = AllRiderLog->Nxt_rider;
	while (nowRider)
	{
		int i = nowRider->Cur_rider->rider_x;
		int j = nowRider->Cur_rider->rider_y;
		int pathMode = nowRider->Cur_rider->path_mode;
		//推算出原来的坐标
		if (i % 2 == 1 && j % 2 == 0) //横向道路
		{
			switch (pathMode)
			{
			case 0:
				j -= 2;
				break;
			case 1:
				i++;
				j++;
				break;
			case 2:
				i++;
				j--;
				break;
			case 3:
				j += 2;
				break;
			case 4:
				i--;
				j++;
				break;
			case 5:
				i--;
				j--;
				break;
			case 6:
				break;
			}
		}
		else if (i % 2 == 0 && j % 2 == 1) //纵向道路
		{
			switch (pathMode)
			{
			case 0:
				i += 2;
				break;
			case 1:
				i++;
				j--;
				break;
			case 2:
				i--;
				j--;
				break;
			case 3:
				i -= 2;
				break;
			case 4:
				i++;
				j++;
				break;
			case 5:
				i--;
				j++;
				break;
			case 6:
				break;
			}
		}
		if (i % 2 == 1 && j % 2 == 0) //横向道路
		{
			if (pathMode >= 0 && pathMode <= 2) //先往右走
			{
				if (*countTime <= 152) //往右走
				{
					getimage(rider_img, "Rider(right).png", 26, 24);
					putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300) //再往不同方向走
				{
					switch (pathMode)
					{
					case 0: //往右走
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
						break;
					case 1: //往上走
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
						break;
					case 2: //往下走
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
						break;
					}
				}
				else //停一会(防止误差)
				{
					switch (pathMode)
					{
					case 0:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 + (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 9, BLACK);
						break;
					case 1:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
						break;
					case 2:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 54, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
						break;
					}
				}
			}
			else if (pathMode >= 3 && pathMode <= 5) //先往左走
			{
				if (*countTime <= 152) //往左走
				{
					getimage(rider_img, "Rider(left).png", 26, 24);
					putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300) //再往不同方向走
				{
					switch (pathMode)
					{
					case 3: //往左走
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (*countTime) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
						break;
					case 4: //往上走
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (*countTime - 152) / 4, BLACK);
						break;
					case 5: //往下走
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (*countTime - 152) / 4, BLACK);
						break;
					}
				}
				else //停一会(防止误差)
				{
					switch (pathMode)
					{
					case 3:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12 - (300) / 4, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
						break;
					case 4:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 - (300 - 152) / 4, BLACK);
						break;
					case 5:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) - 21, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 12 + (300 - 152) / 4, BLACK);
						break;
					}
				}
			}
			else if (pathMode == 6)
			{
				getimage(rider_img, "Rider(right).png", 26, 24);
				putimage_transparent(NULL, rider_img, 25 + j / 2 * (HWID + RWID) + 12, 50 + (i - 1) / 2 * (HWID + RWID) + HWID - 10, BLACK);
			}
		}
		else if (i % 2 == 0 && j % 2 == 1) //纵向道路
		{
			if (pathMode >= 0 && pathMode <= 2) //先往上走
			{
				if (*countTime <= 152) //往上走
				{
					getimage(rider_img, "Rider(up).png", 17, 26);
					putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300) //再往其他方向走
				{
					switch (pathMode)
					{
					case 0: //往上走
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (*countTime) / 4, BLACK);
						break;
					case 1: //往左走
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					case 2: //往右走
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					}
				}
				else //停一会(防止误差)
				{
					switch (pathMode)
					{
					case 0:
						getimage(rider_img, "Rider(up).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 - (300) / 4, BLACK);
						break;
					case 1:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					case 2:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) - 35, BLACK);
						break;
					}
				}
			}
			else if (pathMode >= 3 && pathMode <= 5) //先往下走
			{
				if (*countTime <= 152) //往下走
				{
					getimage(rider_img, "Rider(down).png", 17, 26);
					putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
				}
				else if (*countTime > 152 && *countTime <= 300) //再往其他方向走
				{
					switch (pathMode)
					{
					case 3: //往下走
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (*countTime) / 4, BLACK);
						break;
					case 4: //往左走
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					case 5: //往右走
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (*countTime - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					}
				}
				else //停一会(防止误差)
				{
					switch (pathMode)
					{
					case 3:
						getimage(rider_img, "Rider(down).png", 17, 26);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1 + (300) / 4, BLACK);
						break;
					case 4:
						getimage(rider_img, "Rider(left).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID - 1 - (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					case 5:
						getimage(rider_img, "Rider(right).png", 26, 24);
						putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + (300 - 152) / 4, 50 + i / 2 * (HWID + RWID) + 40, BLACK);
						break;
					}
				}
			}
			else if (pathMode == 6)
			{
				getimage(rider_img, "Rider(down).png", 17, 26);
				putimage_transparent(NULL, rider_img, 25 + (j - 1) / 2 * (HWID + RWID) + HWID + 4, 50 + i / 2 * (HWID + RWID) + 1, BLACK);
			}
		}
		nowRider = nowRider->Nxt_rider;
	}
	if (*cnt_hire)
	{
		char s[11];
		setfont(30, 0, "微软雅黑");
		setcolor(RED);
		setbkmode(TRANSPARENT);
		sprintf(s, "骑手+%d", *cnt_hire);
		outtextrect(RWID + 4 * (HWID + RWID), HWID + 3 * (HWID + RWID) + HWID, 975, 485, s);
	}
	delimage(rider_img);
}

/*
	以下四个函数为地图坐标与画面坐标的转化
 */

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