//
//  userInterface.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 29/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef userInterface_h
#define userInterface_h


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fileRead.h"
#include "dataBaseElManager.h"
#include "makeArrayManager.h"
#include "sortDatabase.h"

void printCarList (listManager * list);
void printPossibleMakes (char ** makesArray);
FILE * openFile (void);

int checkIfEndsWithTXT (char * fileName);
void requestFileToRead (char * pToFileName);
int decideWhatToDo (FILE * sourceFile, char ** makesArray, listManager * list);
FILE * openSaveFile (void);



#endif
