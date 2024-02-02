#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 50
#define ALLOC_ERR -2
#define FILE_ERR -3
#define EXIT_SUCCESS -4


struct _countries;
typedef struct _countries* positionCountries;
struct _cities;
typedef struct _cities* positionCities;

typedef struct _countries {
    char name[MAXLEN];
    int numID;
    positionCities city;
    positionCountries next;
} Countries;

typedef struct _cities {
    char name[MAXLEN];
    positionCities right;
    positionCities left;
} Cities;


int addCountySorted(positionCountries head);
int printList(positionCountries head);
positionCities insertIntoCityTree(positionCities head, char* cityName);
int findCountry(positionCountries head, int countryID);
int inorder(positionCities root);
int printAllCities(positionCountries head);


int main() {
    Countries head = {
        .name = "",
        .numID = 0,
        .city = NULL,
        .next = NULL
    };

    char tempName[MAXLEN];
    int tempID = 0;
    FILE* countriesFile = NULL;
    FILE* citiesFile = NULL;
    countriesFile = fopen("drzave.txt", "r");
    if (!countriesFile)
        return FILE_ERR;

    while (!feof(countriesFile)) {
        fscanf(countriesFile, "%s %d", tempName, &tempID);
        addCountrySorted(&head, tempName, tempID);
    }

    fclose(countriesFile);

    citiesFile = fopen("gradovi.txt", "r");
    if (!citiesFile)
        return FILE_ERR;

    while (!feof(citiesFile)) {
        fscanf(citiesFile, "%s %d", tempName, &tempID);
        insertCityIntoCountry(head.next, tempID, tempName);
    }

    fclose(citiesFile);

    printAllCities(head.next);

    //printList(head.next);
    return 0;
}

int addCountrySorted(positionCountries head, char* countryName, int countryID) {
    positionCountries current = head;
    positionCountries newElement = NULL;

    newElement = (positionCountries)malloc(sizeof(Countries));
    if (!newElement)
        return ALLOC_ERR;

    while (current->next != NULL && (strcmp(current->next->name, countryName) < 0))
        current = current->next;

    newElement->next = current->next;
    current->next = newElement;
    newElement->numID = countryID;
    strcpy(newElement->name, countryName);

    positionCities newCity = NULL;
    newCity = (positionCities)malloc(sizeof(Cities));
    strcpy(newCity->name, "");
    newCity->left = NULL;
    newCity->right = NULL;
    newElement->city = newCity;

    return EXIT_SUCCESS;
}

int printList(positionCountries head) {
    while (head) {
        printf("%s\n", head->name);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

positionCities insertIntoCityTree(positionCities root, char* cityName) {
    if (!root) {
        positionCities newCity = NULL;
        newCity = (positionCities)malloc(sizeof(Cities));
        if (!newCity)
            return ALLOC_ERR;
        newCity->left = NULL;
        newCity->right = NULL;
        strcpy(newCity->name, cityName);
        return newCity;
    }
    if (strcmp(cityName, root->name) < 0)
        root->left = insertIntoCityTree(root->left, cityName);
    else if (strcmp(cityName, root->name) >= 0)
        root->right = insertIntoCityTree(root->right, cityName);
    return root;
}

int insertCityIntoCountry(positionCountries head, int countryID, char* cityName) {
    while (head) {
        if (head->numID == countryID)
            head->city = insertIntoCityTree(head->city, cityName);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int inorder(positionCities root) {
    if (!root) return;
    inorder(root->left);
    printf("%s ", root->name);
    inorder(root->right);
}

int printAllCities(positionCountries head) {
    while (head) {
        printf("%s :", head->name);
        inorder(head->city);
        puts(" ");
        head = head->next;
    }
}