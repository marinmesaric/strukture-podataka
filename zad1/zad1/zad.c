#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define MAX_LINE 1024
#define MAX_POINTS 15
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
		printf("File error!\n");
		return FILE_ERROR_OPEN;
	}
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_SIZE, filePointer);
		cnt++;
	}

	fclose(filePointer);

	return cnt;
}


Student* allocateMemoryAndReadStudents(int noStudents)
{
	int cnt = 0;
	FILE* filePointer = NULL;
	Student* students = NULL;
	students = (Student*)malloc(noStudents * sizeof(Student));

	if (!students)
	{
		printf("Memory alloc error!\n");
		return NULL;
	}

	filePointer = fopen("students.txt", "r");

	if (!filePointer)
	{
		printf("File error!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer))
	{
		fscanf(filePointer, " %s %s %lf", students[cnt].name, students[cnt].surname, &students[cnt].points);
		cnt++;
	}

	fclose(filePointer);

	return students;
}

double calculateRelativePoints(double points)
{
	return ((points / MAX_POINTS) * 100);
}

int showStudents(int noStudents, Student* students)
{
	int cnt = 0;

	for (cnt; cnt < noStudents; cnt++)
	{
		printf("Name: %s\t Surname: %s\t Absolute points: %.2lf\t Relative points: %.2lf%\t\n", students[cnt].name,
			students[cnt].surname, students[cnt].points, calculateRelativePoints(students[cnt].points));
	}

	return 0;
}


int main() {
	int noRows;
	Student* students = NULL;
	noRows = readNoRowsInFile();

	if (noRows > 0)
	{
		students = allocateMemoryAndReadStudents(noRows);
		showStudents(noRows, students);

		free(students);
	}

	return 0;
}