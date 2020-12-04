//
//  makeArrayManager.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 30/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef makeArrayManager_h
#define makeArrayManager_h

#include <stdio.h>
#include "dataBaseElManager.h"
#include "userInterface.h"
#include <stdlib.h>
#include <string.h>
#include "fileRead.h"


int nOfDefMakes (char ** makesArray);
char * chooseMake (char ** makesArray, int n);
void addNewMake (char ** makesArray);
void deleteMake (char ** makesArray, listManager * list);
void editMake (char ** makesArray, listManager * list);
void cleanString (char * str, int length);




#endif /* makeArrayManager_h */
