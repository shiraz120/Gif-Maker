#include "dataFunctions.h"
#include "checkData.h"

/*
this function will recieve the milseconds the user wants the frame to appear
if its a negative number the user will be asked for new input
input: none
output: time - the milseconds for the frame
*/
int milSec()
{
	int time = 0;
	do {
		printf("please enter the time in milseconds: ");
		scanf("%d", &time);
		getchar();
		if (time < ZERO)
		{
			printf("the time can not be negative, try again\n");
		}
	} while (time < ZERO);
	return time;
}

/*
this function will receive the name of a frame from the user and if its already exist the user 
will enter a new name
input: head
output: name - the name of the frame
*/
char* nameOfFrame()
{
	char temp[SIZE] = { ZERO };
	char* name = NULL;
	printf("enter name of frame: ");
	myFgets(temp, SIZE);
	name = (char*)malloc(sizeof(char) * strlen(temp) + ONE);
	checkAllocation(name);
	strncpy(name, temp, strlen(temp) + ONE);
	return name;
}

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = ZERO;
}

/*
this function will create a new struct from FrameNode type
input: name, time, path
output: newFrame - the new struct
*/
FrameNode* createNewFrame(int time, char* name, char* path)
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));
	checkAllocation(newFrame);
	FrameNode* newFrameList = (FrameNode*)malloc(sizeof(FrameNode));
	checkAllocation(newFrameList);
	newFrameList->frame = newFrame;
	newFrameList->frame->name = name;
	newFrameList->frame->path = path;
	newFrameList->frame->duration = time;
	newFrameList->next = NULL;
	return newFrameList;
}

/*
receive list name and return the len of it by using own calling in the function
input: head
output: len - the length of the list
*/
int lengthOfList(FrameNode* head)
{
	int len = 0;
	FrameNode* current = head;
	while (current)
	{
		len++;
		current = current->next;
	}
	return len;
}

/*
this function will receive the path of a frame from the user and if its already exist the user
will enter a new name
input: head
output: path - the name of the frame
*/
char* receivePath()
{
	char temp[SIZE] = { ZERO };
	char* path = NULL;
	printf("enter path of file: ");
	myFgets(temp, SIZE);
	path = (char*)malloc(sizeof(char) * strlen(temp) + ONE);
	checkAllocation(path);
	strncpy(path, temp, strlen(temp) + ONE);
	return path;
}

/*
this function will print the menu to the user, receive user's choice and return it
input: none
output: choice - the user's choice from the menu
*/
int menu()
{
	int choice = ZERO;
	do {
		printf("\nHere are all the options you have!\n[0] exit the program\n[1] add new frame to your gif!\n[2] you can also delete frame :D\n[3] oh you wanted to change the frame location? choose 3!\n");
		printf("[4] you can also change the milseconds of specific frame, press 4!\n[5] oh you wanted to change all frames display time to the exact same time? you can do it by choosing 5!\n");
		printf("[6] lets see what we have got so far, choose 6 to print your frames data!.\n[7] you can watch your gif by clicking 7! (you can also choose color, 1 for normal color 0 for black and white!).\n[8] you can also save project in requested file if you choose 8\n[9] you can reverse and play your gif if you choose 9!\n\n");
		printf("\nmake your choice! (0-9): ");
		scanf("%d", &choice);
		getchar();
		if (choice < ZERO || choice > NINE)
		{
			printf("You can only choose between 1-9!\n");
		}
	} while (choice < ZERO || choice > NINE);
	return choice;
}

/*
this function will receive name of frame and return that frame
input: head, name
:output: current- the frame that contains the requested name
*/
FrameNode* returnFrameByName(FrameNode* head, char* name)
{
	FrameNode* current = head;
	while (current && strcmp(current->frame->name, name))
	{
		current = current->next;
	}
	return current;
}

/*
this function will index of frame and return that frame
input: head, index
:output: current- the frame in the requested index
*/
FrameNode* returnFrameByIndex(FrameNode* head, int index)
{
	FrameNode* current = head;
	int currentIndex = ZERO;
	while (current && currentIndex < index-ONE)
	{
		current = current->next;
		currentIndex++;
	}
	return current;
}

/*
this function will receive the variable that points on a requested variable in the linked list and return it
input: head, variable
output: pointer - the variable that points on variable value
*/
FrameNode* receivePointerToVariable(FrameNode* head, FrameNode* variable)
{
	FrameNode* current = head;
	FrameNode* pointer = NULL;
	if (!strcmp(head->frame->name, variable->frame->name))
	{
		pointer = head; // if the head and the variable are equal it will return the head
	}
	else
	{
		while (current && (pointer == NULL))
		{
			if (current->next && !strcmp(current->next->frame->name, variable->frame->name))
			{
				pointer = current; // find the pointer to variable in the linked list and return it
			}
			current = current->next;
		}
	}
	return pointer;
}