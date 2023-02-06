#include "checkData.h"

/*
this function will check if a given path is open able and return indicator about it (1- open able 0- not open able)
input: path, type
output: indicator (open able or not)
*/
int checkOpenFile(char* path, char* type)
{
	int indicator = ZERO;
	FILE* fileOpen = fopen(path, type);
	if (fileOpen)
	{
		indicator = TRUE;
		fclose(fileOpen);
	}
	else
	{
		printf("couldnt open %s.\n", path);
		indicator = FALSE;
	}
	return indicator;
}

/*
this function will check that malloc allocation worked well
input: ptr
output: none
*/
void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation error!\n");
		exit(ONE);
	}
}

/*
this function will receive name of frame and check it's existence return 1 if exist and 0 if not
input: head, nameToCheck
output: indicator (exist or not)
*/
int checkFrameExistence(FrameNode* head, char* nameToCheck)
{
	FrameNode* current = head;
	int indicator = FALSE;
	if (head != NULL)
	{
		while (current && strcmp(nameToCheck, current->frame->name))
		{
			current = current->next; // name doesnt exist
		}
		if (current && !strcmp(nameToCheck, current->frame->name))
		{
			indicator = TRUE; // name exist
		}
	}
	return indicator;
}