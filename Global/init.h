#ifndef _INIT
#define _INIT
#include "header.h"

void initMap()
{
    int i;
    for(i = 0; i <= 16; i++)
	{
		for(j = 0; j <= 16; j++)
		{
			if((i % 2) != (j % 2)) // 初始化道路
			{
				Map[i][j] = 0;
			}
			else Map[i][j] = 1; // 初始化房屋
		}
	}
}

#endif