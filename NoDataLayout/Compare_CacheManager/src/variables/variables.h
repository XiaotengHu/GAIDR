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
#define NUM_XY  4
#define ACCURACY 20
#define SIZE_ZONE 1000
#define AREA_THRESHOLD 0.50

/* mysql variables */
#define DB_HOST_NAME "localhost"
#define DB_USER_NAME "root"
#define DB_PASSWORD  "1"
#define DB_DB_NAME   "PA"
#define SHELL_PATH1  "bash /home/summer/workspace/RemoveFile.sh /home/summer/disks/hdd2/ReplicaOne/"
#define SHELL_PATH2  "bash /home/summer/workspace/RemoveFile.sh /home/summer/disks/hdd2/ReplicaOne/"

#define SERVER_PORT  9090
#define PORT 9099
#define CACHEPORT  9096
#define CACHESENDPORT  9097
#define BYTES_OF_FOLDER 4096
#define TOTAL_REPLICA_SIZE 1024*1024*10

#define SERVER_IP "127.0.0.1"
#define SERVER1_IP "127.0.0.1"
#define SERVER2_IP "127.0.0.1"

#define LOCAL_IP  "127.0.0.1"

#define PATTERN ","

#define Replica_PATHONE "/home/summer/disks/hdd2/ReplicaOne/"
#define ORIGINAL_SOURCE_PATH "/home/summer/disks/hdd2/FITS/DATA/"
#define TARGET_PATH "/home/summer/disks/hdd2/TargetFITS/"
#define Replica_PATHTWO "/home/summer/disks/hdd2/ReplicaTwo/"



#endif /* SRC_VARIABLES_VARIABLES_H_ */
