#include "LinkedList.h"
#include "checkData.h"
#include "dataFunctions.h"

/*
this function will free a requested linked list and all it's variables
input: head
output: none
*/
void freeList(FrameNode** head)
{
	FrameNode* current = *head;
	FrameNode* temp = NULL;
	while (current)
	{
		temp = current->next;
		free(current->frame->name);
		free(current->frame->path);
		free(current->frame);
		free(current);
		current = temp;
	}
	*head = NULL;
}

/*
this function will add new frame to linked list
input: head
output: none
*/
void addNewFrame(FrameNode** head)
{
	FrameNode* newFrame = NULL;
	char* name = NULL;
	int time = ZERO;
	char* path = NULL;
	name = nameOfFrame();
	while (checkFrameExistence(*head, name))
	{
		printf("Frame name is already taken, please enter another one\n");
		free(name);
		name = nameOfFrame();
	}
	time = milSec();
	path = receivePath();
	if (checkOpenFile(path, "rb"))
	{
		newFrame = createNewFrame(time, name, path);
		insertLast(head, newFrame);
		printf("***Frame created!***\n\n");
	}
	else
	{
		free(path);
		free(name);
	}
}

/*
this function will add last value to the list by connect it to the last value in the list using head value
input: head, newNode
output: none
*/
void insertLast(FrameNode** head, FrameNode* newNode)
{
	FrameNode* current = *head;
	if (*head == NULL)
	{
		newNode->next = *head; // add value as first value
		*head = newNode;
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next; // add value to the list end 
		}
		current->next = newNode;
	}
}

/*
this function will print all the data about each variable in the linked list
input: head
output: none
*/
void printListData(FrameNode* head)
{
	FrameNode* curr = head;
	while (curr)
	{
		printf("[name]: %s	[path]: %s	[time]: %d ms\n", curr->frame->name, curr->frame->path, curr->frame->duration);
		curr = curr->next;
	}
	if (!head)
	{
		printf("Frame list is empty, maybe you should add some frames....\n\n");
	}
}

/*
this function will delete a requested variable from the linked list by using it's name
input: head
output: none
*/
void deleteFrame(FrameNode** head)
{
	char* name = nameOfFrame();
	FrameNode* pointsDelete = NULL;
	FrameNode* delete = NULL;
	if (checkFrameExistence(*head, name))
	{
		delete = returnFrameByName(*head, name);
		if (ZERO == strcmp((*head)->frame->name, name))
		{
			*head = (*head)->next;
		}
		else
		{
			pointsDelete = receivePointerToVariable(*head, delete);
			pointsDelete->next = delete->next;
		}
		free(delete->frame->name);
		free(delete->frame->path);
		free(delete->frame);
		free(delete);
		printf("***%s successfully deleted!***\n\n", name);
	}
	else
	{
		printf("Seems like %s frame doesnt exist, couldnt delete it.\n\n", name);
	}
	free(name);
}

/*
this function will receive the data about replace request and call to function that will receive those variables in the linked list
and call to function that will replace between them
input: head
output: none
*/
void changeFramesLocations(FrameNode** head)
{
	FrameNode* current = *head;
	FrameNode* requested = NULL;
	int length = lengthOfList(*head);
	char* frame = NULL;
	int counter = ZERO;
	int index = 0;
	do {
		frame = nameOfFrame();
		if (!checkFrameExistence(*head, frame))
		{
			printf("Frame doesnt exist! try again with another name\n");
			free(frame);
		}
	} while (!checkFrameExistence(*head, frame));
	do {
		printf("Enter the new location (Between 1-%d): ", length);
		scanf("%d", &index);
		getchar();
		if (index < ONE || index > length)
		{
			printf("The index is out of the list range! try again\n");
		}
	} while (index < ONE || index > length);
	requested = returnFrameByName(*head, frame);
	while (current != requested)
	{
		current = current->next;
		counter += ONE;
	}
	if (index > counter) // replace variables in a smaller index than what was requested
	{
		replaceNormal(head, index, requested, current->next);
	}
	else // replace variables in a bigger index than what was requested
	{
		replaceInReverse(head, index, requested);
	}
	free(frame);
	printf("***Locations successfully replaced!***\n\n");
}

/*
this function will replace between variables in a given linked list. it will replace variables that their index in
the list is bigger than the given index (for example frame5 to index 1)
input: head, index, requested
output: none
*/
void replaceInReverse(FrameNode** head, int index, FrameNode* requested)
{
	FrameNode* pointerToPointer = NULL;
	FrameNode* pointerToRequested = NULL;
	while (returnFrameByIndex(*head, index) != requested) // each time replace requested and it's pointer in the linked list location
	{
		pointerToRequested = receivePointerToVariable(*head, requested);
		pointerToPointer = receivePointerToVariable(*head, pointerToRequested);
		insertIfPointsEachOther(head, pointerToRequested, requested, pointerToPointer);
	}
}

/*
this function will replace variabels in the linked list for example frame 1 to index 3
input: head, index, requested, current
output: none
*/
void replaceNormal(FrameNode** head, int index, FrameNode* requested, FrameNode* current)
{
	while (returnFrameByIndex(*head, index) != requested) // each time replace requested and the value requested points to
	{
		if (requested->next)
		{
			insertIfPointsEachOther(head, requested, current, receivePointerToVariable(*head, requested));
			current = requested->next;
		}
	}
}

/*
this function will replace given variables in a given linked list
input: head, firstFrame, secondFrame, pointsOnFirst
output: none
*/
void insertIfPointsEachOther(FrameNode** head, FrameNode* firstFrame, FrameNode* secondFrame, FrameNode* pointsOnFirst)
{
	if (firstFrame->frame == (*head)->frame)
	{
		*head = (*head)->next;
		firstFrame->next = (*head)->next;
		(*head)->next = firstFrame;
	}
	else
	{
		firstFrame->next = secondFrame->next;
		secondFrame->next = firstFrame;
		pointsOnFirst->next = secondFrame;
	}
}


/*
this function will receive the data for display time replace and call to function that will change the display time
input: head
output: none
*/
void receiveDataForChangeTime(FrameNode** head)
{
	char* name = NULL;
	int time = 0;
	do {
		printf("Enter the name of the frame you want to change it's display time ");
		name = nameOfFrame();
		if (!checkFrameExistence(*head, name))
		{
			printf("Frame doesnt exist!\n");
			free(name);
		}
	} while (!checkFrameExistence(*head, name));
	changeMilSec(head, name, milSec());
	printf("***Display time for %s Frame successfully replaced!***\n\n", name);
	free(name);
}

/*
this function will receive name of a requested frame, head pointer and requested time and replace that requested frame current time
to the new requested time
input: head, time, nameOfFrame
output: none
*/
void changeMilSec(FrameNode** head, char* nameOfFrame, int time)
{
	FrameNode* current = *head;
	while (current && strcmp(current->frame->name, nameOfFrame))
	{
		current = current->next;
	}
	current->frame->duration = time;
}

/*
this function will receive head pointer and ask for requested time and replace all frames in the linked list
to the new requested time
input: head
output: none
*/
void changeAllMilSec(FrameNode** head)
{
	FrameNode* current = *head;
	int time = milSec();
	while (current)
	{
		changeMilSec(head, current->frame->name, time);
		current = current->next;
	}
	printf("***Display time for all Frames successfully replaced!***\n\n");
}

/*
this function will reverse the list from the end to the start
input: head
output: none
*/
void reverseLine(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* last = NULL;
	FrameNode* nextFrame = NULL;
	int counter = ZERO;
	while (curr)
	{
		nextFrame = curr->next; // receive next frame
		curr->next = last; // the next frame in the current value equal to the previous frame
		last = curr; // previous frame now equal to current frame
		curr = nextFrame; // current frame now equal to next frame
	}
	*head = last;
}

/*
this function will receive color choice from user 0 - black and white 1- default image color
input: none
output: user's choice - the color
*/
int receiveColorChoice()
{
	int color = 0;
	do {
		printf("[0] black and white gif\n[1] default colors gif\n");
		scanf("%d", &color);
		getchar();
		if (color<ZERO || color>ONE)
		{
			printf("you can only choose 1 or 0!\n\n");
		}
	} while (color<ZERO || color>ONE);
	return color;
}