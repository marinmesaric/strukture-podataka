#include <stdio.h>
#define MAX_SIZE 50
#define MAX_LINE 1024
#define FILE_ERROR_OPEN -1


typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;


int readNoRowsInFile() {
	int cnt = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		//printf();
	}
}


int main() {
	int noRows = 0;




	return 0;
}

