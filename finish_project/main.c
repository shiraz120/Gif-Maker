#include "LinkedList.h"
#include "upProject.h"
#include "view.h"
#include "dataFunctions.h"

int main()
{
	int choice = ZERO;
	FrameNode* head = NULL;
	do {
		printf("[0] choose 0 to create new project\n[1] choose 1 to upload an existng project\n");
		scanf("%d", &choice);
		getchar();
		if (choice<ZERO || choice>ONE)
		{
			printf("you can only choose 1 or 0!\n\n");
		}
	} while (choice<ZERO || choice>ONE);
	if (choice == ONE)
	{
		uploadProject(&head); // upload requested existing project
	}
	do {
		choice = menu();
		switch (choice)
		{
		case ONE:
			addNewFrame(&head); // add new frame to the linked list
			break;
		case TWO:
			deleteFrame(&head); // delete requested frame from the linked list
			break;
		case THREE:
			changeFramesLocations(&head); // change the frame locations in the linked list
			break;
		case FOUR:
			receiveDataForChangeTime(&head); // change a requested frame display time
			break;
		case FIVE:
			changeAllMilSec(&head); // change all the linked list frames time to the same display time
			break;
		case SIX:
			printListData(head); // print the linked list that contains all the gif frames and their data
			break;
		case SEVEN:
			play(head, receiveColorChoice()); // play the gif in black and white or default colors
			break;
		case EIGHT:
			saveProject(head); // save project in a format to txt file
			break;
		case NINE:
			reverseLine(&head); // reverse the gif play it and return the gif to what it was
			play(head, ONE);
			reverseLine(&head);
			break;
		}
	} while (choice != ZERO);
	printf("would like to see you again!\n");
	freeList(&head);
	getchar();
}