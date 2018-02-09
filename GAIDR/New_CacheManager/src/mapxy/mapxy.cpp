/*
 * 
 * Created on: Dec 30, 2017
 * Author: Xiaoteng Hu
 * Description:mapxy.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */

#include "mapxy.h"

int * mapXY(int startx, int starty, int endx, int endy){
	int *xy;
	xy = new int[NUM_XY];

	int scale = SIZE_ZONE/ACCURACY;

    xy[0] = (startx/scale)*scale;
    xy[1] = (starty/scale)*scale;

    if(xy[0] == 0){
    	xy[0] = 1;
    }
    if(xy[1] == 0){
    	xy[1] = 1;
    }

    if(endx%scale){
    	xy[2] = (endx/scale +1)*scale;
    }else{
    	xy[2] = (endx/scale)*scale;
    }

    if(endy%scale){
    	xy[3] = (endy/scale+1)*scale;
    }else{
    	xy[3] = (endy/scale)*scale;
    }
    return xy;

}


