#include <stdio.h>
#include <stdlib.h>

#define MAX_BODOVA 50
#define MAX_NAME 30
#define MAX_LASTNAME 30

typedef struct students {
    char name[MAX_NAME];
    char lastname[MAX_LASTNAME];
    int points;
} stud;


//function for reading whole file
int readingFileLoop(FILE *fp) {
    int counter = 0;
    char line[100];

    while (fgets(line, sizeof(line), fp)) {
        counter++;
    }

    return counter;
}

int main() {
    int counter = 0;
    double relativePoints = 0;

    FILE *fp = fopen("student.txt", "r");
    if (!fp) {
        printf("Error at reading file.\n");
        return 1;
    }

    //Calling a function and testing it
    counter = readingFileLoop(fp);
    if (counter == 0) {
        printf("File is empty\n");
        fclose(fp);
        return 0;
    }


    //alocating memory and testin it
    stud *students = (stud *)malloc(sizeof(stud) * counter);
    if (!students) {
        printf("Error in alocating memory\n");
        fclose(fp);
        return 1;
    }

    rewind(fp);

    //loop to read all data from file
    for (int i = 0; i < counter; i++) {
        if (fscanf(fp, "%30s %30s %d", students[i].name, students[i].lastname, &students[i].points) != 3){
            printf("Error reading record %d\n", i + 1);
            fclose(fp);
            free(students);
            return 2;
        }
    }

    //loop for writing all students with there data in terminal
    for (int i = 0; i < counter; i++) {
        relativePoints = (double)students[i].points / MAX_BODOVA * 100;
        printf("%s %s %d %f\n", students[i].name, students[i].lastname, students[i].points, relativePoints);
    }

    fclose(fp);
    free(students);

    return 0;
}