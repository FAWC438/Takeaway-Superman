#include "../Global/header.h"

void push_back_rider(Rider *NewRider, RiderList *List) //骑手入队
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