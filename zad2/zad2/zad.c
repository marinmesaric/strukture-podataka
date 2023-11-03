#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 50
#define NO_PERSON_FOUND NULL
#define EXIT_SUCCESS -2

struct _Person;

typedef struct _Person* Position;

typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;


Position createPerson()
{
	Position newPerson = NULL;
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear = 0;

	newPerson = malloc(sizeof(Person));

	if (!newPerson)
	{
		printf("Can't allocate memory!\n");
		return NULL;
	}

	printf("Enter name:\n");
	scanf(" %s", name);
	printf("Enter surname:\n");
	scanf(" %s", surname);
	printf("Enter birth year:\n");
	scanf(" %d", &birthYear);

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	return newPerson;
}


Position findLast(Position head) {
	Position current = head;

	while (current->next != NULL)
	{
		current = current->next;
	}

	return current;
}


int addToFrontOfTheList(Position head) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;

}


int addToEndOfTheList(Position head) {
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		last = findLast(head);
		newPerson->next = last->next;
		last->next = newPerson;
	}

	return EXIT_SUCCESS;
}


char* enterSurname() { //??
	char surname[MAX_LENGTH] = { 0 };
	printf("Enter surname:\n");
	scanf(" %s", surname);
	return surname;
}


int findPerson(Position firstItem) {
	Position current = firstItem;
	char surname[MAX_LENGTH] = { 0 };

	if (firstItem == NULL) return NO_PERSON_FOUND; 

	strcpy(surname, enterSurname());
	
	do {
		if (strcmp(current->surname, surname) == 0) {
			return current;
		}
		else {
			current = current->next;
		}
	} while (current);
}


int printList(Position firstElement) {
	Position current = firstElement;
	if (!firstElement)
	{
		printf("Empty list!\n");
	}
	for (; current != NULL; current = current->next)
	{
		printf("Name: %s\t Surname: %s\t Birth year: %d\t\n", current->name, current->surname, current->birthYear);
	}
}


int deletePerson(Position head) {
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };

	strcpy(surname, enterSurname());

	if (head->next) {
		Position previous = NULL;

		while (current->next && strcmp(current->surname, surname) != 0) {
			previous = current;
			current = current->next;
		}

		if (previous && previous->next && strcmp(current->surname, surname) == 0) {
			//printPerson(current); test
			previous->next = current->next;
			free(current);
		}
		else {
			return NO_PERSON_FOUND;
		}
	}

}


int insertAfterPerson(Position person) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		newPerson->next = person->next;
		person->next = newPerson;
	}

	return EXIT_SUCCESS;
}


Position findPrevious(Position head) {
	Position current = head;
	char surname[MAX_LENGTH] = { 0 };

	if (!head->next) {
		printf("Empty list!\n");
		return NO_PERSON_FOUND;
	}

	do {
		if (strcmp(current->next->surname, surname) == 0) return current;
		else current = current->next;
	} while (current->next != NULL);
}


int menu(Position head)
{
	char choice = '\0';
	while (1)
	{
		printf("...");
		scanf(" %c", &choice);
		switch (choice) {
		case 'A':
			addToFrontOfTheList(head);
			continue;
		case 'B':
			continue;
		case 'E':
			addToEndOfTheList(head);
			continue;
		case 'P':
			continue;
		}
	}
}


int main()
{
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position current = &head;

	menu(&head);

	while (current->next != NULL) {
		deletePerson(current);
	}

	return 0;
}