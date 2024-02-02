/*
Napisati program kojim se
a) Sluèajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u binarno stablo
pretraživanja. Zatim ispišemo to stablo u preorder naèinu ispisa.
b) Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u proizvoljno
definiranoj datoteci.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 300
#define UPPER 700
#define EXIT_SUCCESS -1
#define ALLOC_ERR -2
#define FILE_ERR -3


struct _node;
typedef struct _node* Position;
typedef struct _node {
	int value;
	Position left;
	Position right;
} Node;


int deleteFromFile(Position root, char* fileName);
Position delete(Position root, int val);
Position insert(Position root, int val);
int randomNum();
int preorder(Position root);


int main() {
	srand(time(0));
	Position root = NULL;
	root = insert(root, randomNum());
	for (int i = 0; i < 100; i++)
		insert(root, randomNum());

	preorder(root);
	puts(" ");
	deleteFromFile(root, "dat.txt");
	preorder(root);
	return 0;
}

Position insert(Position root, int val) {
	if (!root) {
		Position newNode = NULL;
		newNode = (Position)malloc(sizeof(Node));
		if (!newNode)
			return ALLOC_ERR;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->value = val;
		return newNode;
	}
	if (val < root->value)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	return root;
}

int randomNum() {
	return rand() % (UPPER - LOWER + 1) + LOWER;
}

int preorder(Position root) {
	if (root) {
		
		preorder(root->left);
		printf("%d ", root->value);
		preorder(root->right);
	}
	return EXIT_SUCCESS;
}

Position delete(Position root, int val) {
	Position successor = NULL;
	
	if (!root) {
		puts("not in tree");
	}
	else if (val < root->value)
		root->left = delete(root->left, val);
	else if (val > root->value)
		root->right = delete(root->right, val);
	else if (root->left && root->right) {
		successor = root->right;
		while (successor->left)
			successor = successor->left;
		root->value = successor->value;
		root->right = delete(root->right, successor->value);
	}
	else {
		successor = root;
		if (root->left)
			root = root->left;
		else
			root = root->right;
		free(successor);
	}
	return root;
}

int deleteFromFile(Position root, char* fileName) {
	FILE* filePointer = NULL;
	filePointer = fopen(fileName, "r");
	int tempNum = 0;

	while (!feof(filePointer)) {
		fscanf(filePointer, "%d", &tempNum);
		root = delete(root, tempNum);
	}
	return EXIT_SUCCESS;
}