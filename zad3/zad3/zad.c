#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 50
#define NO_PERSON_FOUND NULL
#define EXIT_SUCCESS -2
#define EXIT_FAILURE -3

struct _Person;

typedef struct _Person* Position;

typedef struct _Person {
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} Person;

Position createPerson();
Position findLast(Position head);
int addToFrontOfTheList(Position head);
int addToEndOfTheList(Position head);
int menu(Position head);
Position findPerson(Position firstItem);
int addAfter(Position head, char* selected);
int addBefore(Position head, char* selected);
int sort(Position head);
int swapItems(Position first, Position second);
int addToFrontOfTheListFromFile(Position head, char* name, char* surname, int birthYear);
int writeFile(Position head, char* fileName);
int readFile(Position head, char* fileName);



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

char* enterSurname() {
	char surname[MAX_LENGTH] = { 0 };
	printf("Enter surname:\n");
	scanf(" %s", surname);
	return surname;
}

Position findPerson(Position firstItem) {
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
	char surname[MAX_LENGTH] = { 0 };
	while (1)
	{
		puts("A/B/C/D/E/F/G/H/I/J");
		scanf(" %c", &choice);
		switch (choice) {
		case 'A':
			addToFrontOfTheList(head);
			continue;
		case 'B':
			printList(head);
			continue;
		case 'C':
			addToEndOfTheList(head);
			continue;
		case 'E':
			deletePerson(findPerson(head->next));
			continue;
		case 'D':
			printf("%p\n", findPerson(head->next));
			continue;
		case 'F':
			puts("unesi prezime osobe iza koje se unosi nova: ");
			scanf("%s", surname);
			addAfter(head, surname);
			continue;
		case 'G':
			puts("unesi prezime osobe ispred koje se unosi nova: ");
			scanf("%s", surname);
			addBefore(head, surname);
			continue;
		case 'H':
			sort(head);
			puts("sortirano!");
			continue;
		case 'I':
			puts("upisivanje u datoteku \"file1.txt\"...");
			writeFile(head, "file1.txt");
			puts("upisano!");
			continue;
		case 'J':
			puts("upisivanje iz datoteke \"file.txt\"...");
			readFile(head, "file.txt");
			puts("upisano!");
			continue;
		}
	}
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

int addAfter(Position head, char* selected)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}
	newPerson = createPerson();
	if (!newPerson)
		return EXIT_FAILURE;
	while (head->next != NULL)
	{
		if (strcmp(head->surname, selected) == 0)
		{
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int addBefore(Position head, char* selected)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		printf("couldn't allocate memory");
		return EXIT_FAILURE;
	}
	newPerson = createPerson();
	if (!newPerson)
		return EXIT_FAILURE;
	while (head != NULL)
	{
		if (strcmp(head->next->surname, selected) == 0)
		{
			newPerson->next = head->next;
			head->next = newPerson;
			break;
		}
		head = head->next;
	}

	return EXIT_SUCCESS;
}

int sort(Position head) {
	int swapped = 0;
	Position lastPersonRead = NULL;
	Position start = head;

	if (!start) {
		printf("Empty list!\n");
		return EXIT_FAILURE;
	}
	else if (!head->next) {
		printf("Only single element in list!\n");
		return EXIT_SUCCESS;
	}

	do {
		swapped = 0;
		Position current = start;

		while (current->next != lastPersonRead) {
			if (strcmp(current->surname, current->next->surname) > 0) {
				swapItems(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		lastPersonRead = current;
	} while (swapped);

	return EXIT_SUCCESS;
}

int swapItems(Position first, Position second) {
	char tempName[MAX_LENGTH];
	char tempSurname[MAX_LENGTH];
	int tempBirthYear;

	strcpy(tempName, first->name);
	strcpy(tempSurname, first->surname);
	tempBirthYear = first->birthYear;

	strcpy(first->name, second->name);
	strcpy(first->surname, second->surname);
	first->birthYear = second->birthYear;

	strcpy(second->name, tempName);
	strcpy(second->surname, tempSurname);
	second->birthYear = tempBirthYear;

	return EXIT_SUCCESS;
}

int writeFile(Position head, char* fileName)
{
	FILE* filePointer = fopen(fileName, "w");
	while (head != NULL)
	{
		fprintf(filePointer, "Name: %s, Surname: %s, Birthyear: %d\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}
	return EXIT_SUCCESS;
	fclose(filePointer);
}

int readFile(Position head, char* fileName)
{
	FILE* filePointer = fopen(fileName, "r");
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthyear;

	while (!feof(filePointer))
	{
		fscanf(filePointer, "%s %s %d", name, surname, &birthyear);
		addToFrontOfTheListFromFile(head, name, surname, birthyear);
	}
	fclose(filePointer);
	return EXIT_SUCCESS;
}

int addToFrontOfTheListFromFile(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson)
	{
		printf("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;

	newPerson->next = head->next;
	head->next = newPerson;

	
	return EXIT_SUCCESS;
}
