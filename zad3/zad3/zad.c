#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define EXIT_SUCCESS -1
#define EXIT_FAILURE -2
#define MAX_LINE 1024
#define FILE_ERR -3
#define ALLOC_ERR -4

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coeff;
	int exp;
	Position next;
} Element;


int parseStringIntoList(Position head, char* buffer);
Position createElement(int coefficient, int exponent);
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);
int insertSorted(Position head, Position newElement);
int deleteAfter(Position previous);
int freeMemory(Position head);
int printPoly(Position first);


int main() {
	Element headPoly1 = { .coeff = 0, .exp = 0, .next = NULL };
	Element headPoly2 = { .coeff = 0, .exp = 0, .next = NULL };
	char* fileName = "poly.txt";

	if (readFile(&headPoly1, &headPoly2, fileName) == EXIT_SUCCESS) {
		printPoly(headPoly1.next);
		printPoly(headPoly2.next);
	}

	return 0;
}


int insertSorted(Position head, Position newElement) {
	Position current = head;

	while (current->next != NULL && current->next->exp > newElement->exp) {
		current = current->next;
	}

	mergeAfter(current, newElement);

	return EXIT_SUCCESS;
}


int mergeAfter(Position current, Position newElement) {
	if (current->next == NULL || current->next->exp != newElement->exp) {
		insertAfter(current, newElement);
	}
	else {
		int resultCoeff = current->next->coeff + newElement->coeff;

		if (!resultCoeff) {
			deleteAfter(current);
		}
		else {
			current->next->coeff = resultCoeff;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}


int insertAfter(Position current, Position newElement) {
	newElement->next = current->next;
	current->next = newElement;

	return EXIT_SUCCESS;
}


int printPoly(Position first) {

	if (first) {
		if (first->exp < 0) {
			if (first->coeff == 1) {
				printf("x^(%d)", first->exp);
			}
			else {
				printf("%dx^(%d)", first->coeff, first->exp);
			}
		}
		else {
			if (first->coeff == 1) {
				printf("x^%d", first->exp);
			}
			else {
				printf("%dx^%d", first->coeff, first->exp);
			}
		}

		first = first->next;
	}

	for (; first != NULL; first = first->next) {
		if (first->coeff < 0) {
			if (first->exp < 0) {
				printf(" - %dx^(%d)", abs(first->coeff), first->exp);
			}
			else {
				printf(" - %dx^%d", abs(first->coeff), first->exp);
			}
		}
		else {
			if (first->exp < 0) {
				if (first->coeff == 1) {
					printf(" + x^(%d)", first->exp);
				}
				else {
					printf(" + %dx^(%d)", first->coeff, first->exp);
				}
			}
			else {
				if (first->coeff == 1) {
					printf(" + x^%d", first->exp);
				}
				else {
					printf(" + %dx^%d", first->coeff, first->exp);
				}
			}
		}
	}

	printf("\n");

	return EXIT_SUCCESS;
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

		insertSorted(head, newElement);
		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}


int readFile(Position headPoly1, Position headPoly2, char* fileName) {
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen(fileName, "r");

	if (!filePointer) {
		printf("File error!\n");
		return FILE_ERR;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headPoly1, buffer);

	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(headPoly2, buffer);

	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}


int deleteAfter(Position previous) {
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}


int freeMemory(Position head) {
	Position current = head;

	while (current->next) {
		deleteAfter(current);
	}

	return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent) {
	Position element = NULL;

	element = (Position)malloc(sizeof(Element));

	if (!element) {
		printf("Allocation error!\n");
		return ALLOC_ERR;
	}

	element->coeff = coefficient;
	element->exp = exponent;
	element->next = NULL;

	return element;
}

