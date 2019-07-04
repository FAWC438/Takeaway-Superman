#include "../Global/header.h"
/*
    骑手队列尾部添加骑手
 */
void push_back_rider(Rider *NewRider, RiderList *List)
{
    RiderList *NewRiderList = (RiderList *)malloc(sizeof(RiderList));
    NewRiderList->Cur_rider = NewRider;
    RiderList *BackRiderList = List;
    while (BackRiderList->Nxt_rider)
        BackRiderList = BackRiderList->Nxt_rider;
    BackRiderList->Nxt_rider = NewRiderList;
    NewRiderList->Pre_rider = BackRiderList;
    NewRiderList->Nxt_rider = NULL;
}