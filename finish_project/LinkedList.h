#define _CRT_SECURE_NO_WARNINGS
#ifndef LINKEDLISTH
#define LINKEDLISTH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE !FALSE

#define TEN 10
#define SIZE 150
#define ZERO 0 
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int	duration;
	char* path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

//option 0
void freeList(FrameNode** head);

// option 1
void addNewFrame(FrameNode** head);
void insertLast(FrameNode** head, FrameNode* newNode);

//option 2
void deleteFrame(FrameNode** head);

//option 3
void changeFramesLocations(FrameNode** head);
void replaceNormal(FrameNode** head, int index, FrameNode* requested, FrameNode* current);
void insertIfPointsEachOther(FrameNode** head, FrameNode* firstFrame, FrameNode* secondFrame, FrameNode* pointsOnFirst);
void replaceInReverse(FrameNode** head, int index, FrameNode* requested);

//option 4
void receiveDataForChangeTime(FrameNode** head);
void changeMilSec(FrameNode** head, char* nameOfFrame, int time);

//option 5
void changeAllMilSec(FrameNode** head);

//option 6
void printListData(FrameNode* head);

//option 7 color (bonus!)
int receiveColorChoice();

//option 9 (bonus!)
void reverseLine(FrameNode** head);
#endif
