// written by Charles Strovel
// Program removes any non-alpha characters from an input file
// writes to a different output file
#include <stdio.h>
#pragma warning(disable: 4996)

#define LOAD_FILE_NAME "Text.txt"
#define SAVE_FILE_NAME "Text2.txt"
#define BUFFER_SIZE 100
#define TRUE 1
#define FALSE 0

int loadFile(const char*, char*);
char* sanitize(char*);
void saveFile(const char*, char*);

int main() {
	// declare variables
	const char* fName = LOAD_FILE_NAME;
	char buffer[BUFFER_SIZE];

	// load the file to buffer. Display error message if there was a problem
	if (loadFile(fName, buffer) == FALSE) {
		printf("Please correct the problem and re-run the program");
		return 1; 
	}

	// sanitize the file. No need to catch in an extra varable
	saveFile(SAVE_FILE_NAME, sanitize(buffer));
	return 0;
}

int loadFile(const char* fName, char* buffer) {
	// create file pointer and open file
	FILE* fPoint = fopen(fName, "r");

	// ensure file was opened correctly
	if (fPoint == NULL) {
		printf("File %s was not found.\n", fName);
		return FALSE;
	}

	// load file contents to buffer.  We can check for a succesful file read at the same time
	if (fgets(buffer, BUFFER_SIZE, fPoint) == NULL) {
		printf("File %s was empty.\n", fName);
		fclose(fPoint);
		return FALSE;
	}
	
	// check for EOF, if EOF is not found the file was too large for the buffer
	if (getc(fPoint) != EOF) {
		printf("File %s was too large.\n", fName);
		fclose(fPoint);
		return FALSE;
	}

	// read was succesful! Close file and return
	fclose(fPoint);
	return TRUE;

}

char* sanitize(char* buffer) {
	// declare variables
	int index = 0;
	int offset = 0;
	static char transpose[BUFFER_SIZE];

	// loop through the string, checking for null character to end loop
	while (buffer[index] != '\0') {
		// lower case letters can be directly transposed
		if (buffer[index] >= 'a' && buffer[index] <= 'z') {
			transpose[index - offset] = buffer[index];
		}
		// upper case letters can be transposed after being converted to lower case
		else if (buffer[index] >= 'A' && buffer[index] <= 'Z') {
			transpose[index - offset] = buffer[index] + 32;
		}
		// if any other character is encountered, it should be ignored and offset adjusted
		else {
			offset++;
		}
		// in all cases, the index should be moved up by one
		index++;
	}

	// ensure the null character is afixed to the end of the string
	transpose[index - offset] = '\0';
	buffer = transpose;
}

void saveFile(const char* fName, char* buffer) {
	// open file for writing
	int index = 0;
	FILE* fPointer = fopen(fName, "w");
	while (buffer[index] != '\0') {
		fputc(buffer[index], fPointer);
		index++;
	}
	fclose(fPointer);
}