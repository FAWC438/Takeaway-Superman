#include "../Global/header.h"

void push_back_rider(Rider *NewRider,RiderList *OldList) //骑手入队
{
    RiderList *NewRiderList = (RiderList *)malloc(sizeof(RiderList));
    NewRiderList->Cur_rider = NewRider;
    RiderList *BackRiderList = OldList;
    while (BackRiderList->Nxt_rider)
        BackRiderList = BackRiderList->Nxt_rider;
    BackRiderList->Nxt_rider = NewRiderList;
    NewRiderList->Pre_rider = BackRiderList;
    NewRiderList->Nxt_rider = NULL;    
}
