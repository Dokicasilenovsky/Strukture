#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 128

typedef struct Polinom* Position;

typedef struct Polinom{

    int koef;
    int expo;
    Position next;

}Poli;

Position allocate(){

    Position newPoli = (Position)malloc(sizeof(Poli));

    return newPoli;
}

Position initHead(){

    Position newPoli = allocate();

    if(newPoli == NULL){
        return NULL;
    }

    newPoli->koef = 0;
    newPoli->expo = 0;
    newPoli->next = NULL;

    return newPoli;
}

//Insert element fun
int insertElement(Position p, int k, int e){

    while(p->next != NULL){

        if(p->next->expo == e){
            p->next->koef = p->next->koef + k;
            return 0;
        }

        else if(p->next->expo < e){
            break;
        }

        p = p->next;
    }

    Position newPoli = allocate();
    if(newPoli == NULL){
        return -1;
    }
    newPoli->koef = k;
    newPoli->expo = e;
    newPoli->next = p->next;
    p->next = newPoli;

    return 0;
}

//Mostly just test function to see if it works
int PRINT(Position p){

    p = p->next;

    while(p != NULL){

        printf("%dx%d ", p->koef, p->expo);

        p = p->next;
    }

    return 0;
}

//Copy one list to other by (mistake) smart design it can be used as adder
int copyList(Position funFrom, Position funTo){
    
    funFrom = funFrom->next;
    
    while(funFrom != NULL){

        insertElement(funTo, funFrom->koef, funFrom->expo);
        funFrom = funFrom->next;
    }

    return 0;
}

//Function that deletes all elements in list except head
int deleteList(Position p){

    Position temp;

    while(p->next != NULL){
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    
    return 0;
}

//This works trust me bro
int addPoli(Position Head, Position fun1, Position fun2){
    copyList(fun1, Head);
    copyList(fun2, Head);

    return 0;
}

//Function taht multiplies 2 functions
int multPoli(Position Head, Position fun1, Position fun2){

    Position temp = NULL;

    fun1 = fun1->next;

    while(fun1 != NULL){

        temp = fun2->next;

        while(temp != NULL){
            insertElement(Head, fun1->koef * temp->koef, fun1->expo + temp->expo);
            temp = temp->next;
        }

        fun1 = fun1->next;
    }

    return 0;
}

//Most of function happens here so it start with reading file then it goes in other way
int readFile(Position Head, int checker){

    if(checker != 1 && checker != 2){
        return -5;
    }

    FILE* fp = fopen("polinomi.txt", "r");

    if(fp == NULL){
        return -2;
    }

    Position fun1 = initHead();
    Position fun2 = initHead();

    if(fun1 == NULL || fun2 == NULL){
        free(fun1);
        free(fun2);
        fclose(fp);
        return -1;
    }

    int lineCounter = 0;
    int k, e, n;
    char line[MAX_LINE];
    char* p = NULL;

    while(fgets(line, MAX_LINE, fp) != NULL){

        p = line;

        if(lineCounter == 0){
            while(sscanf(p, " %dx%d%n", &k, &e, &n) == 2){
                insertElement(fun1, k, e);
                p = p + n;
            }
        }

        else{
            while(sscanf(p, " %dx%d%n", &k, &e, &n) == 2){
                insertElement(fun2, k, e);
                p = p + n;
            }
        }

        lineCounter++;


        if(lineCounter == 1){
            continue;
        }

        deleteList(Head);

        if(checker == 1){
            addPoli(Head, fun1, fun2);
        }

        else if(checker == 2){
            multPoli(Head, fun1, fun2);
        }

        deleteList(fun1);
        deleteList(fun2);
        copyList(Head, fun1);

    }

    fclose(fp);

    PRINT(Head);
    printf("\n");

    deleteList(fun1);
    deleteList(fun2);
    free(fun1);
    free(fun2);

    return 0;
}


int main(){

    Position Head1 = initHead();
    Position Head2 = initHead();

    if(Head1 == NULL || Head2 == NULL){
        free(Head1);
        free(Head2);
        return -1;
    }

    readFile(Head1, 1);
    readFile(Head2, 2);


    return 0;
}