
#include "./Global/header.h"

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
