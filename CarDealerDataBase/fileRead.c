//
//  fileReadAndWrite.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 29/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "fileRead.h"




//funkcja pomija jeden wiersz tekstu w pliku
static void skipOneLineInFile (FILE * sourceFile) {
    char ch;
    while ( (ch = getc(sourceFile)) != '\n' && ch != EOF )
        continue;
}


//funkcja czytająca jedną z pięciu możliwych marek
static char * readOnePossibleMake (FILE * sourceFile) {
    
    char * possibleMake = (char *)malloc(25 * sizeof(char));
    
    int i;
    for (i = 0; i < 2; i++)
        getc(sourceFile);
    
    if (fgets(possibleMake, 25, sourceFile) == NULL) {
        int k;
        for (k = 0; k < 25; k++)
            possibleMake[k] = '\0';
    }
    
    
    
    
    
    int j = 0;
    while (possibleMake[j] != '\0') {
        if (possibleMake[j] == '\n') {
            possibleMake[j] = '\0';
            break;
        }
        if (j == 23)    //jeśli fgets nie pobral entera to czyszcze dalsze wejscie
            skipOneLineInFile(sourceFile);
        j++;
    }
    
    return possibleMake;
        
}



//Funkcja odczytująca z pliku jakie marki mogą być wpisane w polu "make" w rekordzie
//zwraca NULL jeśli wczytywanie zakończyło się niepowodzeniem
char ** readPossibleMakes (FILE * sourceFile) {
    if (sourceFile == NULL) {
        puts("Błąd wczytywania możliwych marek");
        return NULL;
    }
    char ** possibleMakes = (char **)malloc(5 * sizeof(char *));
    
    skipOneLineInFile(sourceFile); //pomija pierwszą linie
    
    int i;
    for (i = 0; i < 5; i++)
        possibleMakes[i] = readOnePossibleMake(sourceFile);
        
    skipOneLineInFile(sourceFile);
    skipOneLineInFile(sourceFile);
    
    
    return possibleMakes;
}


static void changeSpacesToZeroSigns (char * string, int arrayLength) {
    int i = arrayLength - 1;
    
    while (string[i] == ' ')
        i--;
    
    if(i != arrayLength - 1)
        i++;
    
    for(; i < arrayLength; i++)
        string[i] = '\0';
}


static void deleteNewLine (char * string, int stringLength) {
    int i = stringLength - 1;
    while (string[i] != '\n' && i >= 0)
        i--;
    
    string[i] = '\0';
}


//funkcja czytająca i wpisująca do struktury pojedyńczą linię z dataBase.txt
//jeśli doszliśmy do końca pliku, funkcja zwraca wskaźnik NULL
static CAR * readOneElement (FILE * sourceFile) {
    char oneLine[90];
    
    if(fgets(oneLine, 90, sourceFile) == NULL)
        return NULL;
    
    if(oneLine[0] == '\n')
        return NULL;
    
    
    CAR * readElement = (CAR *)malloc(sizeof(CAR));
    readElement -> model = (char *)malloc(25 * sizeof(char));
    readElement -> make = (char *)malloc(25 * sizeof(char));
    
    
    
    strncpy(readElement -> make, oneLine, 25);
    changeSpacesToZeroSigns(readElement -> make, 25);
    
    strncpy(readElement -> model, &(oneLine[25]), 25);
    changeSpacesToZeroSigns(readElement -> model, 25);
    
    char year[8];
    strncpy(year, &(oneLine[50]), 8);
    changeSpacesToZeroSigns(year, 8);
    readElement -> yearOfProduction = atoi(year);
    
    char Mileage[15];
    strncpy(Mileage, &(oneLine[58]), 15);
    changeSpacesToZeroSigns(Mileage, 15);
    readElement -> mileage = atoi(Mileage);
    
    char owner[6];
    strncpy(owner, &(oneLine[73]), 6);
    changeSpacesToZeroSigns(owner, 6);
    readElement -> owner = atoi(owner);
    
    char price[11];
    strncpy(price, &(oneLine[79]), 11);
    deleteNewLine(price, 11);
    readElement -> price = atoi(price);
    
    return readElement;
}


//tworzy listę dwukierunkową wszystkich rekordów
listManager * createElementsList (FILE * sourceFile) {
    if (sourceFile == NULL)
        return NULL;
    
    CAR * firstCar = readOneElement(sourceFile);
    CAR * secondCar;

    
    listManager * createdList = (listManager *)malloc(sizeof(listManager));
    if(firstCar == NULL) {
        createdList -> listHead = NULL;
        createdList -> listTail = NULL;
        return createdList;
    }

    
    createdList -> listHead = firstCar;
    
    while ( (secondCar = readOneElement(sourceFile)) != NULL ) {
        firstCar -> next = secondCar;
        secondCar -> previous = firstCar;
        firstCar = secondCar;
    }
    firstCar -> next = NULL;
    createdList -> listTail = firstCar;
    
    return createdList;
}

