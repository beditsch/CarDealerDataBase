//
//  sortDatabase.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 03/06/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "sortDatabase.h"


static void singleCarIntoArray (CAR * carArray, CAR * car, int arrayIndex) {
    
    if (carArray == NULL)
        return;
    if (car == NULL)
        return;
    

    
    strncpy((carArray[arrayIndex].make), car -> make, 25);
    strncpy(carArray[arrayIndex].model, car -> model, 25);
    carArray[arrayIndex].yearOfProduction = car -> yearOfProduction;
    carArray[arrayIndex].mileage = car -> mileage;
    carArray[arrayIndex].owner = car -> owner;
    carArray[arrayIndex].price = car -> price;
}


static void deallocateList (listManager * list) {
    if (list == NULL)
        return;
    if (list -> listHead == NULL)
        return;
    CAR * car, * temp;
    car = list -> listHead;
    while (car != NULL) {
        temp = car;
        car = car -> next;
        free(temp);
    }
    list -> listHead = NULL;
    list -> listTail = NULL;
}




static CAR * carListToArray (listManager * list) {
    if (list == NULL)
        return NULL;
    if (list -> listHead == NULL)
        return NULL;
    
    int nOfEl = findCurrentNumberOfElements(list);
    
    CAR * carArray = (CAR *)malloc(nOfEl * sizeof(CAR));
    
    int k;
    for (k = 0; k < nOfEl; k++) {
        carArray[k].make = malloc(25 * sizeof(char));
        carArray[k].model = malloc(25 * sizeof(char));
    }
    
    CAR * temp = list -> listHead;
    
    int i;
    for (i = 0; i < nOfEl; i++) {
        singleCarIntoArray(carArray, temp, i);
        temp = temp -> next;
    }
    deallocateList(list);
    
    return carArray;
}



static CAR *  pointerToSingleArrayEl (CAR car) {
    CAR * newCar = (CAR *)malloc(sizeof(CAR));
    newCar -> make = malloc(25 * sizeof(char));
    newCar -> model = malloc(25 * sizeof(char));
    
    strncpy(newCar -> make, car.make, 25);
    strncpy(newCar -> model, car.model, 25);
    newCar -> yearOfProduction = car.yearOfProduction;
    newCar -> price = car.price;
    newCar -> mileage = car.mileage;
    newCar -> owner = car.owner;
    newCar -> next = NULL;
    newCar -> previous = NULL;
    return newCar;
}



//funkcja tworząca liste i przypisująca jej poczatek i koniec odpowiednim polom zainicjalizowanej wczesniej struktury listManager
static void carArrayToList (listManager * list, CAR * carArray, int nOfElements) {
    if (list == NULL)
        return;
    if (carArray == NULL)
        return;
    
    int i;
    list -> listHead = pointerToSingleArrayEl(carArray[0]);
    CAR * temp;
    temp = list -> listHead;
    
    for (i = 1; i < nOfElements; i++) {
        temp -> next = pointerToSingleArrayEl(carArray[i]);
        temp -> next -> previous = temp;
        temp = temp -> next;
    }
    list -> listTail = temp;
    
    free(carArray);
    
}










int compareMake (const void * p1, const void * p2) {

    int arraySize = 25;
    int i;
    char c1, c2;
    
    for (i = 0; i < arraySize; i++) {
        c1 = (((CAR *)p1) -> make)[i];
        c2 = (((CAR *)p2) -> make)[i];
        if (toupper(c1) < toupper(c2))
            return -1;
        if(toupper(c1) > toupper(c2))
            return 1;
        
        if (c1 == '\0' && c2 == '\0')
            return 0;
        if (i == 24)
            return 0;
    }
    return 0;
}

int compareModel (const void * p1, const void * p2) {
    
    int arraySize = 25;
    int i;
    char c1, c2;
    
    for (i = 0; i < arraySize; i++) {
        c1 = (((CAR *)p1) -> model)[i];
        c2 = (((CAR *)p2) -> model)[i];
        if (toupper(c1) < toupper(c2))
            return -1;
        if(toupper(c1) > toupper(c2))
            return 1;
        
        if (c1 == '\0' && c2 == '\0')
            return 0;
        if (i == 24)
            return 0;
    }
    return 0;
}

int comparePrice (const void * p1, const void * p2) {
    int a = ((CAR *)p1) -> price;
    int b =((CAR *)p2) -> price;
    return a - b;
}

int compareOwner (const void * p1, const void * p2) {
    int a = ((CAR *)p1) -> owner;
    int b =((CAR *)p2) -> owner;
    return a - b;
}

int compareMileage (const void * p1, const void * p2) {
    int a = ((CAR *)p1) -> mileage;
    int b =((CAR *)p2) -> mileage;
    return a - b;
}

int compareYear (const void * p1, const void * p2) {
    int a = ((CAR *)p1) -> yearOfProduction;
    int b =((CAR *)p2) -> yearOfProduction;
    return a - b;
}





void sort (int func(const void * p1, const void * p2), listManager * list) {
    int nOfEl = findCurrentNumberOfElements(list);
    
    CAR * carArray = carListToArray(list);
    
    qsort(carArray, nOfEl, sizeof(CAR), func);
    
    carArrayToList(list, carArray, nOfEl);
    
}



void printSortMENU (void) {
    puts("\nWybierz po jakim polu chcesz wykonać sortowanie. Naciśnij odpowiedni klawisz:");
    puts("1 - po marce             2 - po modelu            3 - po roku produkcji");
    puts("4 - po cenie             5 - po przebiegu         6 - po liczbie właścicieli");
}






void callSort (listManager * list) {
    if (findCurrentNumberOfElements(list) < 2) {
        puts("Sortowanie niemożliwe. W bazie muszą być minimum dwa rekordy.");
        return;
    }
    
    printSortMENU();
    
    
    char c = getchar();
    cleanInput();
    
    while (1) {
        switch (c) {
            case '1':
                sort(compareMake, list);
                return;
            case '2':
                sort(compareModel, list);
                return;
            case '3':
                sort(compareYear, list);
                return;
            case '4':
                sort(comparePrice, list);
                return;
            case '5':
                sort(compareMileage, list);
                return;
            case '6':
                sort(compareOwner, list);
                return;
                
            default:
                puts("Wprowadziłeś błędne dane, wprowadź poprawne.");
                printSortMENU();
                c = getchar();
                cleanInput();
                break;
        }
    }
    
    return;

}
