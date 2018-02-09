#ifndef SRC_TRACK_TRACK_H_
#define SRC_TRACK_TRACK_H_

#include "../utils/csvOper.h"
#include "../variables/variables.h"

void record(list<RequestInfo> requestList);


void recordRate(string hitRate);


void genReqFromTrack(list<RequestInfo> *requestsList);

#endif
