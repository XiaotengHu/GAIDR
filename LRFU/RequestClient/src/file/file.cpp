#include "file.h"

void initFiles(FileInfo *files){

	srand((int)time(0));

	for(int i=0; i<NUM_FILES; i++){
		files[i].filename = i;
		files[i].hot = 1 + random(NUM_HOT);
		files[i].type = 1 +random(NUM_TYPE);
		files[i].hotzone = 1+ random(NUM_HOT_ZONE);
		files[i].reqcounts = 0;
		files[i].idletime = 0;
	}
}
