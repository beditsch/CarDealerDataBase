//
//  fileWrite.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 31/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "fileWrite.h"


static void putNTimes (char c, int n, FILE * fp) {
    if (fp == NULL)
        return;
    
    int i;
    for (i = 0; i < n; i++)
        putc((int)c, fp);
}

static int integerLength (int n) {
    if (n == 0)
        return 1;
    n = floor(log10(abs(n))) + 1;
    return n;
}

//funkcja wpisująca zgodnie ze schematem wpisywania info o jednym aucie do pliku tekstowego;
static void putSingleCarInfo (CAR * car, FILE * fp) {
    if (fp == NULL)
        return;
    if (car == NULL)
        return;

    int length;

    length = (int)strlen(car -> make);
    fputs(car -> make, fp);
    putNTimes(' ', 25 - length, fp);

    length = (int)strlen(car -> model);
    fputs(car -> model, fp);
    putNTimes(' ', 25 - length, fp);

    length = integerLength(car -> yearOfProduction);
    fprintf(fp, "%d", car -> yearOfProduction);
    putNTimes(' ', 8 - length, fp);

    length = integerLength(car -> mileage);
    fprintf(fp, "%d", car -> mileage);
    putNTimes(' ', 15 - length, fp);

    length = integerLength(car -> owner);
    fprintf(fp, "%d", car -> owner);
    putNTimes(' ', 6 - length, fp);

    fprintf(fp, "%d\n", car -> price);
}



void putCarList (listManager * list, FILE * fp) {
    if (list == NULL)
        return;
    if ( (list -> listHead) == NULL)
        return;
    if (fp == NULL)
        return;

    int i = 1, length;

    CAR * car;
    car = list -> listHead;

    while (car != NULL) {
        length = integerLength(i);
        i++;
        putSingleCarInfo(car, fp);
        car = car -> next;
    }
}


void putPossibleMakes (char ** makesArray, FILE * fp) {
    if (makesArray == NULL)
        return;
    if (fp == NULL)
        return;
    
    int i;
    int maxmakes = 5;
    int counter = 1;
    for (i = 0; i < maxmakes; i++) {
        fprintf(fp, "%d)%s\n", counter++, makesArray[i]);
    }
}


void writeFile(char ** makesArray, listManager * list, FILE * fp) {
    
    fputs("Possible makes:\n", fp);
    putPossibleMakes(makesArray, fp);
    fputs("Database elements:\n", fp);
    fputs("Make                     Model                    Year    Mileage        Owner Price\n", fp);
    putCarList(list, fp);
}




