#include "track.h"



void recordRate(string hitRate){

	writeCSV(RATE_RECORD_PATH, hitRate);
}

void record(list<RequestInfo> requestsList){
	writeCSV(RESULT_PATH, requestsList);
}
