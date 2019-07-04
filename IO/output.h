
#include "../Global/header.h"

void outputOnFileKey()
{
    FILE *fPtr;
    if ((fPtr = fopen("output.txt", "a")) == NULL)
    {
        printf("Can't not open the output.txt");
        return;
    }

    printf("时间: %d\n", Time);
    fprintf(fPtr, "时间: %d\n", Time);
    printf("钱: %d\n", CompanyMoney); // 这里指现金，没有加上骑手资产
    fprintf(fPtr, "钱: %d\n", CompanyMoney);
    printf("接单数: %d\n", CompanyOrderSum);
    fprintf(fPtr, "接单数: %d\n", CompanyOrderSum);
    printf("完成数: %d; ", CompanyOrderFinish);
    fprintf(fPtr, "完成数: %d; ", CompanyOrderFinish);
    printf("结单: ");
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
                printf("%d", HeadOrder->Cur_order->id);
                fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
            }
            else
            {
                printf(" %d", HeadOrder->Cur_order->id);
                fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
            }
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
    printf(";\n");
    fprintf(fPtr, ";\n");
    printf("超时数: %d;", CompanyOrderOverTime);
    fprintf(fPtr, "超时数: %d;", CompanyOrderOverTime);
    printf("罚单: ");
    fprintf(fPtr, "罚单: ");
    // 遍历此时刻是否有罚单的
    HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    flag = 0;
    while (HeadOrder)
    {
        if (Time - HeadOrder->Cur_order->begin_time > FINE_FIRST_TIME && HeadOrder->Cur_order->status != 3) // 起始时间距现在大于30且未完成
        {
            if (!flag)
            {
                flag = 1;
                printf("%d", HeadOrder->Cur_order->id);
                fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
            }
            else
            {
                printf(" %d", HeadOrder->Cur_order->id);
                fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
            }
        }
        HeadOrder = HeadOrder->Nxt_order;
    }
    printf(";\n");
    fprintf(fPtr, ";\n");
    // 输出各骑手状态
    RiderList *HeadRider = AllRiderLog;
    HeadRider = HeadRider->Nxt_rider;
    while (HeadRider)
    {
        printf("骑手%d位置: %d, %d; ", HeadRider->Cur_rider->rider_x, HeadRider->Cur_rider->rider_y);
        fprintf(fPtr, "骑手%d位置: %d, %d; ", HeadRider->Cur_rider->rider_x, HeadRider->Cur_rider->rider_y);
        printf("停靠: ");
        fprintf(fPtr, "停靠: ");
        // TODO: 停靠判断
    }

    fclose(fPtr);
}

void outputMap()
{
    int i, j, k;

    initMap(); // 初始化地图
    // 初始化房屋类型
    OrderList *HeadOrder = AllOrderLog;
    HeadOrder = HeadOrder->Nxt_order;
    whlie(HeadOrder)
    {
        Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_x] = 2;
        Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_x] = 3;
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
