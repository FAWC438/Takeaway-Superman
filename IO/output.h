
#include "../Global/header.h"

// TODO: 打印骑手轨迹以调整。
/*
    停靠判断并输出
*/
void printNearBy(Rider *nowRider, FILE *fPtr)
{
    int i;
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    int restFlag = 0, dustFlag = 0;
    
    for(i = 0; i <= 3; i++)
    {
        restFlag = 0;
        dustFlag = 0;
        int now_x = nowRider->rider_x + dx[i];
        int now_y = nowRider->rider_y + dy[i];
        OrderList *tmpOrder = nowRider->Bag->Nxt_order;
        while(tmpOrder)
        {
            if(tmpOrder->Cur_order->rest_x == now_x && tmpOrder->Cur_order->rest_y == now_y && tmpOrder->Cur_order->end_time == Time)    // 说明此位置房子作为餐厅有任务完成
            {
                restFlag = 1;
            }
            if(tmpOrder->Cur_order->cust_x == now_x && tmpOrder->Cur_order->cust_y == now_y && tmpOrder->Cur_order->end_time == Time)    // 说明此位置房子作为宿舍有任务完成
            {
                dustFlag = 1;
            }
            if(dustFlag && restFlag)
                fprintf(fPtr, " 餐客 %d %d", now_x, now_y);
            else if(restFlag)
                fprintf(fPtr, " 餐厅 %d %d", now_x, now_y);
            else if(dustFlag)
                fprintf(fPtr, " 食客 %d %d", now_x, now_y);
            tmpOrder = tmpOrder->Nxt_order;
        }
    }
    
}
/*
    输出在文件中
*/
void outputOnFile()
{
    FILE *fPtr;
    if ((fPtr = fopen("output.txt", "a")) == NULL)
    {
        printf("Can't not open the output.txt");
        return;
    }
    fprintf(fPtr, "时间: %d\n", Time);
    fprintf(fPtr, "钱: %d\n", CompanyMoney);
    fprintf(fPtr, "接单数: %d\n", CompanyOrderSum);
    fprintf(fPtr, "完成数: %d; ", CompanyOrderFinish);
    fprintf(fPtr, "结单: ");
    // 遍历全部订单判断是否有此时刻结单的
    OrderList *HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    int flag = 0; // 判断是否为第一个输出的订单号
    while (HeadOrder)
    {
        if (HeadOrder->Cur_order->end_time == Time && HeadOrder->Cur_order->status == 3)
        {
            if (!flag)
            {
                flag = 1;
                fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
            }
            else
            {
                fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
            }
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
    fprintf(fPtr, ";\n");
    fprintf(fPtr, "超时数: %d;", CompanyOrderOverTime);
    fprintf(fPtr, "罚单: ");
    // 遍历此时刻是否有罚单的
    HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    flag = 0;
    while (HeadOrder)
    {
        if (Time - HeadOrder->Cur_order->begin_time == FINE_FIRST_TIME + 1 && HeadOrder->Cur_order->status != 3) // 起始时间距现在等于31且未完成
        {
            if (!flag)
            {
                flag = 1;
                fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
            }
            else
            {
                fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
            }
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
    fprintf(fPtr, ";\n");
    // 输出各骑手状态
    RiderList *HeadRider = AllRiderLog;
    HeadRider = HeadRider->Nxt_rider;
    while (HeadRider)
    {
        fprintf(fPtr, "骑手%d位置: %d, %d; ", HeadRider->Cur_rider->rider_x, HeadRider->Cur_rider->rider_y);
        fprintf(fPtr, "停靠:");
        printNearBy(HeadRider->Cur_rider, fPtr);
        HeadRider = HeadRider->Nxt_rider;
        fprintf(fPtr, ";\n");
    }

    fclose(fPtr);
}
/*
    以文字的形式输出在屏幕上，注意刷新频率不同！！！
*/
void outputKey()
{
	printf("时间: %d\n", Time);
    printf("钱: %d\n", CompanyMoney); // 这里指现金，没有加上骑手资产
    printf("接单数: %d\n", CompanyOrderSum);
    printf("完成数: %d\n", CompanyOrderFinish);
    printf("超时数: %d;", CompanyOrderOverTime);
}
/*
    以地图的形式输出在屏幕上
*/
void outputMap()    // 餐客形式没考虑
{
    int i, j, k;

    initMap(); // 初始化地图
    // 初始化房屋类型
    OrderList *HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    whlie(HeadOrder)
    {
        // 待与停靠函数协调
        if((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3) || (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time))
        {
            Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_x] = 2; // 餐厅地图更新
            Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_x] = 3; // 宿舍地图更新
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
    // 初始化骑手位置
    RiderList *HeadRider = AllRiderLog;
    HeadRider = HeadRider->Nxt_rider;
    while (HeadRider)
    {
        Map[HeadRider->Cur_rider->rider_x][HeadRider->Cur_rider->rider_y] = 4 // 骑手地图更新
        HeadRider = HeadRider->Nxt_rider;
    }

    for (i = 0; i <= 16; i++)
    {
        if (i % 2 == 0)
        { // 有房子的行
            for (k = 0; k <= 3; k++)
            {
                for (j = 0; j <= 16; j++)
                {
                    if (j % 2 == 0)
                    {
                        if (k == 0)
                        {
                            printf("__________");
                        }
                        else if (k == 1)
                        {
                            printf("|        |");
                        }
                        else if (k == 2)
                        {
                            printf("|  ");
                            /*
                            if (Map[i][j] == 0) { // 道路
								printf("    ");
							}
							*/
                            if (Map[i][j] == 1)
                            { // 房子
                                printf("    ");
                            }
                            else if (Map[i][j] == 2)
                            { // 餐厅
                                printf("餐厅");
                            }
                            else
                            { // 宿舍
                                printf("宿舍");
                            }
                            printf("  |");
                        }
                        else
                        {
                            printf("|________|");
                        }
                    }
                    else
                    {
                        if (k == 2)
                        {
                            if (Map[i][j] == 0)
                            { // 道路
                                printf("    ");
                            }
                            else if (Map[i][j] == 4)
                            { // 骑手
                                printf("骑手");
                            }
                        }
                        else
                        {
                            printf("    ");
                        }
                    }
                }
                printf("\n");
            }
        }
        else
        { // 无房子的行
            for (int j = 0; j <= 16; j++)
            {
                if (j % 2 == 0)
                {
                    printf("   ");
                    if (Map[i][j] == 0)
                    {
                        printf("    ");
                    }
                    if (Map[i][j] == 4)
                    {
                        printf("骑手");
                    }
                    printf("   ");
                }
                else
                {
                    printf("    ");
                }
            }
            printf("\n");
        }
    }
}
