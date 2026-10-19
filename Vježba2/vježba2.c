#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;

typedef struct Person{

    char name[20];
    char lastName[20];
    int year;
    Position next;

}Person;

Position allocate(){

    Position newPerson = (Position)malloc(sizeof(Person));

    return newPerson;
}

//Initialise Head function
Position initHead(){

    Position newPerson = allocate();

    strcpy(newPerson->name, "");
    strcpy(newPerson->lastName, "");
    newPerson->year = 0;
    newPerson->next = NULL;


    return newPerson;
}

//Insert element at the begin 
int insertBegin(char* name, char* lastName, int year, Position head){

    Position newPerson = allocate();
    if(!newPerson){
        printf("Allocate Error\n");
        return -2;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->year = year;
    newPerson->next = head->next;
    head->next = newPerson;

    return 0;
}

//Insert element at the end
int insertAfter(char* name, char* lastName, int year, Position P){

    Position newP = allocate();
    if(!newP){
        printf("Allocate Error\n");
        return -2;
    }

    while(P->next != NULL){
        P = P->next;
    }

    newP->next = P->next;
    P->next = newP;

    strcpy(newP->name, name);
    strcpy(newP->lastName, lastName);
    newP->year = year;

    return 0;
}

//Print all the elements
int printList(Position p){
    p = p->next;
    if(p == NULL){
        printf("No elements error\n");
        return -3;
    }

    while(p != NULL){
        printf("%s %s %d\n", p->name, p->lastName, p->year);
        p = p->next;
    }

    return 0;
}

//Locate specific element by lastname
Position locateElement(Position p, char* lastName){

    while(p->next != NULL && strcmp(p->next->lastName, lastName) != 0){
        p = p->next;
    }
    if(p->next == NULL){
        printf("Element %s does not exist\n", lastName);
        return NULL;
    }

    return p;
}

//Delete located element
int deleteElement(Position p, char* lastName){

    Position locP = locateElement(p, lastName);
    if(locP == NULL){
        return -1;
    }

    Position delP = locP->next;
    locP->next = locP->next->next;
    free(delP);

    return 0;
}

//free whole list
int freeList(Position p){

    while(p != NULL){
        Position nextEle = p->next;
        free(p);
        p = nextEle;
    }

    return 0;
}


int main(){

    Position Head = initHead();
    if(Head == NULL){
        return -1;
    }


    insertBegin("Mihael", "Purar", 2004, Head);
    insertBegin("Ivan", "Stepinac", 2005, Head);
    insertBegin("Mateo", "Juretic", 2005, Head);
    insertBegin("Duje", "Mandalinic", 2006, Head);
    insertAfter("Mateo", "Claude", 2026, Head);
    deleteElement(Head, "Juretic");
    deleteElement(Head, "Krolo");

    printList(Head);

    freeList(Head);

    printList(Head);

    return 0;

}

