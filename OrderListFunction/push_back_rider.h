#include "../Global/header.h"

void push_back_rider(Rider *NewRider,RiderList *OldList)            //骑手入队
{
    RiderList *NewRiderList = (RiderList *)malloc(sizeof(RiderList));
    NewRiderList->Cur_rider = NewRider;
    RiderList *BackRiderList = List;
    while (BackRiderList->Nxt_Rider)
        BackRiderList = BackRiderList->Nxt_Rider;
    BackRiderList->Nxt_Rider = NewRiderList;
    NewRiderList->Pre_Rider = BackRiderList;
    NewRiderList->Nxt_Rider = NULL;    
}
