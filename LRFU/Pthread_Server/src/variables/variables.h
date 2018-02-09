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

#define Replica_PATHONE "/home/summer/disks/hdd1/ReplicaOne/"
#define Replica_PATHTWO "/home/summer/disks/hdd2/ReplicaTwo/"
#define ORIGINAL_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/"
#define TARGET_PATH "/home/summer/disks/ssd1/TargetFITS/"
#define RATE_RECORD_PATH "/home/summer/disks/hdd1/Rate.csv"
#define RESULT_PATH "/home/summer/disks/hdd1/Result.csv"





#endif /* SRC_VARIABLES_VARIABLES_H_ */
