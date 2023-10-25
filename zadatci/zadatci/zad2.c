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

	// ? newPerson = malloc(sizeof(Person);

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

char* enterSurname()
{
	char surname[MAX_LENGTH] = { 0 };
	// fali
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

int printList(Position firstElement) {
	Position current = firstElement;
	if (!firstElement)
	{
		printf("Empty list!\n");
	}
	for (; current != NULL; current = current->next)
	{

	}
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
		case 'a':
			addToFrontOfTheList(head);
			continue;
		case 'E':
		case 'e':
			addToEndOfTheList(head);
			continue;
		case 'P':
			continue;
		}
	}
}

int main()
{
	Person head = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };

	menu(&head);


	return 0;
}