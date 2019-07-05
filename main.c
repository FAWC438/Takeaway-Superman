#include "./Global/header.h"

int main()
{
    if (inputFileOrder())
        ;
    else
        inputKeyOrder();

    while (1)//胜利条件 
    {
        Time++;
        //招募骑手
        while(CompanyMoney>=400)
        {
            hireRider();
        }
        //派单之前把骑手背包完成的订单弹出
        initRiderBag();
        //派单算法
        //判断是否超时或破产
        isAnyOrderOverTime();
        //骑手移动
        AllRiderMove();
        //判断每一个订单是否完成
        //完成每一个需要完成的订单 但是在骑手背包里不弹出刚完成的订单 （输出文件时判断停靠使用）
        RiderList *tempRider = AllRiderLog->Nxt_rider;
        while(tempRider)
        {
            OrderList *tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
            while(tempOrder)
            {
                if(isComplishOrder(tempOrder))
                {
                    complishOrder(tempOrder);
                }
                tempOrder = tempOrder->Nxt_order;
            }
            tempRider = tempRider->Nxt_rider;
        }
            //TODO:完成订单时输出控制台窗口
            system("clr");
            outputMap();
        //输出文件
        outputOnFileKey();
        sleep(TIME_UNIT);
    }
    printf("Successful!"); 
    return 0;
}