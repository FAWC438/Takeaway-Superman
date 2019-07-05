#include "./Global/header.h"

int main()
{
    if(inputFileOrder())
        ;
    else
        inputKeyOrder();
    
    while(AllOrderLog->Nxt_order)
    {
        //派单

        //判断是否超时
        isAnyOrderOverTime();
        //送单
        
        //输出
        system("clr");
        outputOnFileKey();
        outputMap();
        sleep(TIME_UNIT);
    }
    printf("Successful!")
    return 0;
}