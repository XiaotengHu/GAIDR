/*
 * 
 * Created on: Dec 26, 2017
 * Author: Xiaoteng Hu
 * Description:variables.h
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#ifndef SRC_VARIABLES_VARIABLES_H_
#define SRC_VARIABLES_VARIABLES_H_


/* Global variables*/
#define NUM_MAX 1024
#define NUM_FILES 500
#define NUM_HOT 10
#define NUM_TYPE 4
#define NUM_HOT_ZONE 4
#define SIZE_ZONE 1000

/* mysql variables */
#define DB_HOST_NAME "localhost"
#define DB_USER_NAME "root"
#define DB_PASSWORD  "1"
#define DB_DB_NAME   "PA"

#define SERVER_PORT  9090
#define PORT 9099
#define CACHEPORT  9096

#define SERVER_IP "127.0.0.1"
#define SERVER1_IP "127.0.0.1"
#define SERVER2_IP "127.0.0.1"

#define LOCAL_IP  "127.0.0.1"

#define PATTERN ","

#define Replica_PATHONE "/home/summer/disks/hdd2/ReplicaOne/"
#define Replica_PATHTWO "/home/summer/disks/hdd2/ReplicaTwo/"
#define ORIGINAL_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/"
#define TARGET_PATH "/home/summer/disks/hdd2/TargetFITS/"
#define RATE_RECORD_PATH "/home/summer/disks/hdd2/RateCompare.csv"
#define RESULT_PATH "/home/summer/disks/hdd2/ResultCompare.csv"

#define TRACK_PATH "./track/normal.csv"



#endif /* SRC_VARIABLES_VARIABLES_H_ */
