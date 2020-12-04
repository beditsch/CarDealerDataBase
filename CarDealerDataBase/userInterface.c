//
//  userInterface.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 29/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "userInterface.h"

static void printNTimes (char c, int n) {
    int i;
    for (i = 0; i < n; i++)
        putchar((int)c);
}

static int integerLength (int n) {
    if (n == 0)
        return 1;
    n = floor(log10(abs(n))) + 1;
    return n;
}


int checkIfEndsWithTXT (char * fileName) {
    if (fileName == NULL)
        return 0;

    int i = 24;
    while (fileName[i] == '\0' || fileName[i] == EOF)
        --i;
    
    if (i >= 4 && fileName[i] == 't' && fileName[i - 1] == 'x' && fileName[i - 2] == 't' && fileName[i - 3] == '.')
        return 1;
    else
        return 0;
}


static void printSingleCarInfo (CAR * car) {
    if (car == NULL)
        return;
    
    int length;
    
    length = (int)strlen(car -> make);
    printf("%s", car -> make);
    printNTimes(' ', 25 - length);
    
    length = (int)strlen(car -> model);
    printf("%s", car -> model);
    printNTimes(' ', 25 - length);
    
    length = integerLength(car -> yearOfProduction);
    printf("%d", car -> yearOfProduction);
    printNTimes(' ', 8 - length);
    
    length = integerLength(car -> mileage);
    printf("%d", car -> mileage);
    printNTimes(' ', 15 - length);
    
    length = integerLength(car -> owner);
    printf("%d", car -> owner);
    printNTimes(' ', 6 - length);
    
    printf("%d\n", car -> price);
}



void printCarList (listManager * list) {
    if (list == NULL)
        return;
    if ( (list -> listHead) == NULL) {
        puts("Żadna pozycja nie została zdefiniowana.");
        return;
    }
    int i = 1, length;
    
    puts("   Marka                    Model                    Rok     Przebieg       Wł.   Cena");
    CAR * car;
    car = list -> listHead;
    
    while (car != NULL) {
        length = integerLength(i);
        printf("%d", i);
        printNTimes(' ', 4 - length);
        i++;
        printSingleCarInfo(car);
        car = car -> next;
    }
}


void printPossibleMakes (char ** makesArray) {
    int i;
    int maxmakes = 5;
    int counter = 1;
    for (i = 0; i < maxmakes; i++) {
        
        if (makesArray[i][0] == '\0');
        else
            printf("%d) %s    ", counter++, makesArray[i]);
    }
    if (counter == 1)
        puts("Żadna marka nie została zdefiniowana.");
    putchar('\n');
}



void requestFileToRead (char * pToFileName) {
    
    
    char * fileName = pToFileName;
    
    puts("Podaj nazwę pliku do wczytania, wpisz n - jeśli chcesz utworzyć nową bazę (max 24 znaki, nazwę pliku zakończ rozszerzeniem .txt) :");
    fgets(fileName, 25, stdin);
    
    dealWithInputAndNewLine(fileName, 25);
    
    
    
    if (fileName[0] == 'n' && fileName[1] == '\0') {
        FILE * fp = fopen("nowy.txt", "w");
        fclose(fp);
        
        strncpy(fileName, "nowy.txt", 25);
        
        return;
    }
    
    
    while (checkIfEndsWithTXT(fileName) != 1) {
        puts("Podałeś błędną nazwę. Podaj nazwę pliku do wczytania, wpisz n - jeśli chcesz utworzyć nową bazę (max 24 znaki, nazwę pliku zakończ rozszerzeniem .txt) :");
        fgets(fileName, 25, stdin);
        dealWithInputAndNewLine(fileName, 25);
        
        if (fileName[0] == 'n' && fileName[1] == '\0') {
            FILE * fp = fopen("nowy", "w");
            fclose(fp);
            
            strncpy(fileName, "nowy.txt", 25);
            dealWithInputAndNewLine(fileName, 25);
            
            return;
        }
    }
    return;
}


FILE * openFile (void) {
    FILE * fp = NULL;
    char * fileName = (char *)malloc(25 * sizeof(char));
    int i;
    for (i = 0; i < 25; i++)
        fileName[i] = '\0';
    
    requestFileToRead(fileName);
    fp = fopen(fileName, "r");
    
    while (fp == NULL) {
        printf("Podałeś błędną nazwę. ");
    requestFileToRead(fileName);
        fp = fopen(fileName, "r");
    }
    free(fileName);
    return fp;
}


void printMENU (void) {
    puts("\nWybierz czynność, którą chcesz przeprowadzić. Naciśnij odpowiedni klawisz:");
    puts("1 - dodaj rekord              2 - usuń rekord               3 - edytuj rekord");
    puts("4 - dodaj wartość \"marka\"     5 - usuń wartość \"marka\"      6 - edytuj wartość \"marka\"");
    puts("7 - sortuj bazę               8 - wyczyść bazę              k - koniec");
}




int decideWhatToDo (FILE * sourceFile, char ** makesArray, listManager * list){
    printMENU();
    
    char c = getchar();
    cleanInput();
    
    switch (c) {
        case '1':
            addElement(list, makesArray);
            return 1;
            break;
        case '2':
            deleteElement(list);
            return 1;
            break;
        case '3':
            editElement(list, makesArray);
            return 1;
            break;
        case '4':
            addNewMake(makesArray);
            return 1;
            break;
        case '5':
            deleteMake(makesArray, list);
            return 1;
            break;
        case '6':
            editMake(makesArray, list);
            return 1;
            break;
        case '7':
            callSort(list);
            return 1;
            break;
        case '8':
            cleanDataBase(makesArray, list);
            return 1;
            break;
        case 'k':
            return 0;
            break;

        default:
            puts("Wprowadziłeś błędne dane, wprowadź poprawne.");
            return 2;
            break;
    }
    
    return 2;
}




static void requestFileToWrite (char * pToFileName) {
    
    
    char * fileName = pToFileName;
    
    puts("Podaj nazwę pliku do zapisania bazy (max 24 znaki, nazwę pliku zakończ rozszerzeniem .txt) :");
    fgets(fileName, 25, stdin);
    
    dealWithInputAndNewLine(fileName, 25);
    
    
    while (checkIfEndsWithTXT(fileName) != 1) {
        puts("Podałeś błędną nazwę. Podaj nazwę pliku do zapisania (max 24 znaki, nazwę pliku zakończ rozszerzeniem .txt) :");
        fgets(fileName, 25, stdin);
        dealWithInputAndNewLine(fileName, 25);
    }
    return;
}



FILE * openSaveFile (void) {
    FILE * fp = NULL;
    char * fileName = (char *)malloc(25 * sizeof(char));
    int i;
    for (i = 0; i < 25; i++)
        fileName[i] = '\0';
    
    requestFileToWrite(fileName);
    fp = fopen(fileName, "w");

    while (fp == NULL) {
        printf("Coś poszło nie tak. Spróbuj jeszcze raz. ");
        requestFileToWrite(fileName);
        fp = fopen(fileName, "w");
    }
    free(fileName);
    return fp;
}
