#include "track.h"

void record(list<RequestInfo> requestsList){

	writeCSV(REQUEST_RECORD_PATH, requestsList);
}

void recordRate(string hitRate){

	writeCSV(RATE_RECORD_PATH, hitRate);
}

void genReqFromTrack(list<RequestInfo> *requestsList){

	readCSV(TRACK_PATH, requestsList);
}
