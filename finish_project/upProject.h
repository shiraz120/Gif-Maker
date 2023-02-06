#ifndef UPPROJECTH
#define UPPROJECTH
#include "LinkedList.h"

// upload existing video
void uploadProject(FrameNode** head);
char readToDelimiter(FILE* file, char delim, char buffer[SIZE]);
void readIntoVariable(char** variable, char delimiter, char buffer[SIZE], FILE* fileOpen);

//option 8
void saveProject(FrameNode* head);

#endif
