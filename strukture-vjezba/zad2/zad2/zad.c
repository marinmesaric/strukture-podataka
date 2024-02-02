#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 150
#define ALLOC_ERR -2
#define FILE_ERR -3
#define EXIT_SUCCESS -4

struct _node;
typedef struct _node* positionTree;
struct _element;
typedef struct _element* positionList;

typedef struct _node {
	char value[MAXLEN];
	positionTree left;
	positionTree right;
	positionList listHead;
} Node;

typedef struct _element {
	char value[MAXLEN];
	positionList next;
} Element;


positionTree insert(positionTree root, char* val);
int addToList(positionList head, char* val);
void inorder(positionTree root);
positionTree Find(positionTree root, char* val);
int printNum(positionTree root, char* val);

int main() {
	positionTree root = NULL;
	char tempValue[MAXLEN];
	FILE* filePointer = NULL;
	filePointer = fopen("text.txt", "r");
	if (!filePointer)
		return FILE_ERR;
	fscanf(filePointer, "%s", tempValue);
	root = insert(root, tempValue);
	while (!feof(filePointer)) {
		fscanf(filePointer, "%s", tempValue);
		insert(root, tempValue);
	}
	inorder(root);
	puts(" ");
	scanf("%s", tempValue);
	printNum(root, tempValue);

	return 0;
}


positionTree insert(positionTree root, char* val) {
	positionTree newElement = NULL;
	positionList newHead = NULL;
	if (!root) {
		newElement = (positionTree)malloc(sizeof(Node));
		newHead = (positionList)malloc(sizeof(Element));
		newElement->left = NULL;
		newElement->right = NULL;
		newElement->listHead = newHead;
		strcpy(newElement->value, val);
		newHead->next = NULL;
		strcpy(newHead->value, val);
		return newElement;
	}
	if (strcmp(root->value, val) < 0)
		root->left = insert(root->left, val);
	else if (strcmp(root->value, val) > 0)
		root->right = insert(root->right, val);
	else
		addToList(root->listHead, val);
	return root;
}

int addToList(positionList head, char* val) {
	positionList current = head;
	positionList newElement = NULL;
	newElement = (positionList)malloc(sizeof(Element));

	while (current->next) {
		current = current->next;
	}

	current->next = newElement;
	newElement->next = NULL;
	strcpy(newElement->value, val);
}

void inorder(positionTree root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	printf("%s ", root->value);
	inorder(root->right);
}

positionTree Find(positionTree current, char* val)
{
	if (current == NULL)
		return NULL;
	else if (strcmp(val, current->value) > 0)
		return Find(current->left, val);
	else if (strcmp(val, current->value) < 0)
		return Find(current->right, val);
	return current;
}

int printNum(positionTree root, char* val) {
	int counter = 0;
	positionList current = NULL;
	positionTree temp = NULL;
	temp = Find(root, val);
	if (!temp) {
		puts("nema elementa");
		return EXIT_SUCCESS;
	}
	current = temp->listHead;

	while (current) {
		current = current->next;
		counter++;
	}
		
	printf("%s se ponavlja %d puta\n", val, counter);
	return EXIT_SUCCESS;
}