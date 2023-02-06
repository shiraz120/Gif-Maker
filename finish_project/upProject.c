#include "upProject.h"
#include "checkData.h"
#include "dataFunctions.h"

/*
this function will upload existing project
input: head
output: none
*/
void uploadProject(FrameNode** head)
{
	char* path = NULL;
	char buffer[SIZE] = { ZERO };
	char* name = NULL;
	char* pathToRead = NULL;
	int time = 0;
	char reader = ' ';
	path = receivePath();
	while (!checkOpenFile(path, "r"))
	{
		printf("try to enter new file path\n");
		free(path);
		path = receivePath();
	}
	FILE* fileOpen = fopen(path, "r");
	checkAllocation(fileOpen);
	while (reader != EOF)
	{
		readIntoVariable(&name, ',', buffer, fileOpen);
		readIntoVariable(&pathToRead, ',', buffer, fileOpen);
		reader = readToDelimiter(fileOpen, '\n', buffer);
		time = atoi(buffer);
		insertLast(head, createNewFrame(time, name, pathToRead));
	}
	fclose(fileOpen);
	free(path);
}

/*
this function will read into given variable from current location to given delimiter
input: variable, delimiter, buffer, fileOpen
output: none
*/
void readIntoVariable(char** variable, char delimiter, char buffer[SIZE], FILE* fileOpen)
{
	char reader = readToDelimiter(fileOpen, ',', buffer);
	*variable = (char*)malloc(sizeof(char) * (strlen(buffer) + ONE));
	checkAllocation(*variable);
	strncpy(*variable, buffer, strlen(buffer) + ONE);
}

/*
This function reads from a current location to a given delimiter
Input: file, delimiter, buffer
Output: Last read character
*/
char readToDelimiter(FILE* file, char delimiter, char buffer[SIZE])
{
	char* bufferPtr = buffer;
	char reader = ' ';
	while (reader != EOF && reader != delimiter)
	{
		reader = (char)fgetc(file);
		if (reader != EOF && reader != delimiter)
		{
			*bufferPtr = reader;
			bufferPtr++;
		}
	}
	*bufferPtr = NULL;
	return reader;
}


/*
this function will save a project into requested file 
input: head
output: none
*/
void saveProject(FrameNode* head)
{
	char* path = NULL;
	FILE* pathOpen = NULL;
	FrameNode* current = head;
	do {
		path = receivePath();
		pathOpen = fopen(path, "w");
		if (pathOpen == NULL)
		{
			printf("couldnt open file path, try again\n");
			free(path);
		}
	} while (pathOpen == NULL);
	while (current)
	{
		fprintf(pathOpen, "%s,%s,%d", current->frame->name, current->frame->path, current->frame->duration);
		if (current->next)
		{
			fprintf(pathOpen, "\n");
		}
		current = current->next;
	}
	fclose(pathOpen);
	free(path);
	printf("***project saved successfully!***\n");
}