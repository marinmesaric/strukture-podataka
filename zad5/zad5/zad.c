#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	double num;
	Position next;
} Element;


double calculateResult(Position head, char* fileName);
int pushNum(Position head, double number);
double popNum(Position head);
double operation(Position head, char matOperation);


int main() {
	Element head = { .num = 0, .next = NULL };
	double calculationResult = 0.0;

	calculationResult = calculateResult(&head, "postfix.txt");
	printf("%lf\n", calculationResult);
}


int pushNum(Position head, double number) {
	Position newElement;
	newElement = (Position)malloc(sizeof(Element));
	
	newElement->num = number;
	newElement->next = head->next;
	head->next = newElement;

	return 1;
}


double popNum(Position head) {
	double tempValue = 0.0;
	Position temp = NULL;
	temp = head->next;
	tempValue = temp->num;
	head->next = temp->next;

	free(temp);

	return tempValue;
}


double calculateResult(Position head, char* fileName) {
	char* buffer[MAX_LENGTH] = { 0 };
	FILE* filePointer = fopen(fileName, "r");

	fgets(buffer, MAX_LENGTH, filePointer);
	fclose(filePointer);

	int bufferCounter = 0;
	int status = 0;
	double tempNum = 0.0, result = 0.0;
	char tempChar = '\0';
	char* tempBuffer = buffer;


	while (strlen(tempBuffer) > 0) {
		status = sscanf(tempBuffer, " %lf %n", &tempNum, &bufferCounter);
		if (status == 1) {
			pushNum(head, tempNum);
		}
		else {
			sscanf(tempBuffer, " %c %n", &tempChar, &bufferCounter);
			result = operation(head, tempChar);
			pushNum(head, result);
		}
		tempBuffer += bufferCounter;
	}

	return result;
}


double operation(Position head, char matOperation) {
	double num1 = 0, num2 = 0;

	num2 = popNum(head);
	num1 = popNum(head);

	switch (matOperation) {
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	}
}