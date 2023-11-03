#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define EXIT_SUCCESS -1
#define EXIT_FAILURE -2

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coeff;
	int exp;
	Position next;
} Element;

int parseStringINtoList(Position head, char* buffer);
Position createElement(); //arg?
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);
int insertSorted(Position head, Position newElement);
int deleteAfter(Position previous); 
int printPoly(Position head); //arg?


int main() {
	Element headPoly1 = { .coeff = 0, .exp = 0, .next = NULL };

	return 0;
}


int parseStringIntoList(Position head, char* buffer) {
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while (strlen(currentBuffer) > 0) {
		status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);

		if (status != 2) {
			printf("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newElement = createElement(coefficient, exponent);
		if (!newElement) {
			return EXIT_FAILURE;
		}

		currentBuffer += numBytes;
	}
}


int mergeAfter(Position current, Position newElement) {
	if (current->next != NULL || current->next->exp != newElement->exp) {
		//insertAfter
	}
}


int insertAfter(Position current, Position newElement) {

}


int insertSorted(Position head, Position newElement) {
	Position current = head;

	while (current->next != NULL || current->next->exp != newElement->exp) {
		current = current->next;
	}

	mergeAfter(current, newElement);

	return EXIT_SUCCESS;
}


int deleteAfter(Position previous) {
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete; //fali
}


int printPoly(Position head) {

}