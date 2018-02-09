/*
 * track.cpp
 *
 *  Created on: Dec 31, 2017
 *      Author: hong
 */

#include "track.h"


void record(list<RequestInfo> requestsList){
	writeCSV(RESULT_PATH, requestsList);
}


