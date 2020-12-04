//
//  dataBase.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 17/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef dataBaseElManager_h
#define dataBaseElManager_h


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>






typedef struct _car_ {
    char * make;
    char * model;
    int yearOfProduction;
    int mileage;
    int owner;
    int price;
    
    struct _car_ * previous;
    struct _car_ * next;
}CAR;


typedef struct _listManager_ {
    CAR * listHead;
    CAR * listTail;
}listManager;

#include "fileRead.h"
#include "makeArrayManager.h"


void addElement (listManager * listPointer, char ** makesArray);
void deleteElement (listManager * listPointer);
void editElement (listManager * listPointer, char ** makesArray);
void dealWithInputAndNewLine(char * text, int stringLength);
int requestMake (char ** makesList);
void cleanInput (void);
void cleanDataBase (char ** makesArray, listManager * list);
int findCurrentNumberOfElements (listManager * list);

#endif
