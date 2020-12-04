//
//  makeArrayManager.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 30/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "makeArrayManager.h"



int nOfDefMakes (char ** makesArray) {
    int nOfMakes = 0;
    int i;
    for (i = 0; i < 5; i++) {
        if(makesArray[i][0] != '\0')
            nOfMakes++;
    }
    return nOfMakes;
}


//marki sa przechowywane stale w tablicy pieciu ciagów znaków, jeśli jest mniej zdefiniowanych marek, to niektóre ciągi są puste. Funkcja ta zwraca wskaźnik n-tej marki z listy marek.
char * chooseMake (char ** makesArray, int makeNumber) {
    
    int make = 0;
    int i = 0;
    while (make != makeNumber) {
        if (i > 4)
            return NULL;
        if (makesArray[i][0] != '\0') {
            make++;
        }
        i++;
    }
    return makesArray[i - 1];
}

char * findSpaceForNewMake (char ** makesArray) {
    int i;
    for (i = 0; i < 5; i++) {
        if (makesArray[i][0] == '\0')
            break;
    }
    return makesArray[i];
}



void addNewMake (char ** makesArray){
    if (makesArray == NULL)
        return;
    if (nOfDefMakes(makesArray) == 5) {
        puts("Możesz zdefiniować tylko 5 możliwych marek.");
        return;
    }
    puts("Rozpoczynamy procedurę dodawania nowej możliwej marki.");
    char * freeSpace = findSpaceForNewMake(makesArray);
    
    char * make;
    make = malloc(25 * sizeof(char));
    
    puts("Podaj nową markę:");
    fgets(make, 25, stdin);
    
    dealWithInputAndNewLine(make, 25);
    
    while ( (make)[0] == '\n' ||  (make)[0] == '\0' || make[0] == ' ') {
        puts("To nie jest trudne. Podaj poprawnie nową markę:");
        fgets(make, 25, stdin);
        
        dealWithInputAndNewLine(make, 25);
    }
    strncpy(freeSpace, make, 25);
    free(make);
}

void cleanString (char * str, int length) {
    if (str == NULL)
        return;
    int i;
    for (i = 0; i < length; i++)
        str[i] = '\0';
}

void deleteCarsAfterDelMake (listManager * list, char * makeToDelete) {
    if (list == NULL)
        return;
    if (list -> listHead == NULL)
        return;
    
    CAR * car = list -> listHead;
    
    
    while (car != NULL) {
        if (strncmp(car -> make, makeToDelete, 25) == 0){
            if (car == list -> listHead && car == list -> listTail) {
                list -> listHead = NULL;
                list -> listTail = NULL;
                free(car);
            }

            else if (car == list -> listHead) {
                car -> next ->  previous = NULL;
                list -> listHead = car -> next;
                free(car);
            }
            else if (car == list -> listTail) {
                list -> listTail = car -> previous;
                car -> previous -> next = NULL;
                free(car);
            }
            else {
                car -> previous -> next = car -> next;
                car -> next -> previous = car -> previous;
                free(car);
                
            }
        }
        car = car -> next;
    }
}



void deleteMake (char ** makesArray, listManager * list) {
    if (makesArray == NULL)
        return;
    
    if (nOfDefMakes(makesArray) == 0) {
        puts("Lista możliwych marek jest pusta.");
        return;
    }
    puts("Rozpoczynamy procedurę usuwania marki.");    
    int chosenMake = requestMake(makesArray);
    char * pointerToMakeToDelete = chooseMake(makesArray, chosenMake);
    
    deleteCarsAfterDelMake(list, pointerToMakeToDelete);
    
    cleanString(pointerToMakeToDelete, 25);
}





static int requestMakeIDforEditing (int number, char ** makesArray) {
    int ID;
    puts("Podaj numer marki, który chcesz edytować:");
    printPossibleMakes(makesArray);
    while (scanf("%d", &ID) != 1 || ID < 1 || ID > number) {
        
        cleanInput();
        
        puts("Nie wygłupiaj się, podaj poprawny numer marki:");
    }
    return ID;
}


static void changeMakeAfterEditing (listManager * list, char * makeToEdit, char * make) {
    if (list == NULL)
        return;
    if (list -> listHead == NULL)
        return;
    
    CAR * temp = list -> listHead;
    
    while (temp != NULL) {
        if (strncmp(temp -> make, makeToEdit, 25) == 0){
            strncpy(temp -> make, make, 25);
        }
        temp = temp -> next;
    }
}




void editMake (char ** makesArray, listManager * list) {
    if (makesArray == NULL)
        return;
    if (nOfDefMakes(makesArray) == 0) {
        puts("Żadna marka nie jest zdefiniowana, aby edytować markę, musisz ją najpierw dodać.");
        return;
    }
    
    puts("Rozpoczynamy procedurę edytowania marki.");
    
    char * make;
    make = malloc(25 * sizeof(char));
    char * makeToEdit;
    
    int makeID;
    makeID = requestMakeIDforEditing(nOfDefMakes(makesArray), makesArray);
    makeToEdit = chooseMake(makesArray, makeID);
    
    cleanInput();
    puts("Podaj, czym chcesz zastąpić tę markę:");
    
    fgets(make, 25, stdin);
    
    dealWithInputAndNewLine(make, 25);
    
    while ( (make)[0] == '\n' ||  (make)[0] == '\0' || make[0] == ' ') {
        puts("To nie jest trudne. Podaj poprawnie czym chcesz zastąpić tę markę:");
        fgets(make, 25, stdin);
        
        dealWithInputAndNewLine(make, 25);
    }
    
    changeMakeAfterEditing(list, makeToEdit, make);
    
    strncpy(makeToEdit, make, 25);
    free(make);
}

