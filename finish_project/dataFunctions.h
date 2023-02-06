#ifndef DATAFUNCTIONS
#define DATAFUNCTIONS
#include "LinkedList.h"

// receive data
int lengthOfList(FrameNode* head);
int milSec();
char* nameOfFrame();
void myFgets(char str[], int n);
char* receivePath();
FrameNode* returnFrameByName(FrameNode* head, char* name);
FrameNode* returnFrameByIndex(FrameNode* head, int index);
FrameNode* createNewFrame(int time, char* name, char* path);
FrameNode* receivePointerToVariable(FrameNode* head, FrameNode* variable);
int menu();

#endif