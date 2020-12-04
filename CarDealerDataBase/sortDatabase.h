//
//  sortDatabase.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 03/06/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef sortDatabase_h
#define sortDatabase_h

#include <stdio.h>
#include "dataBaseElManager.h"
#include "userInterface.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fileRead.h"
#include "makeArrayManager.h"
#include "fileWrite.h"


void sort (int func(const void * p1, const void * p2), listManager * list);
int compareMake (const void * p1, const void * p2);
int compareModel (const void * p1, const void * p2);
int comparePrice (const void * p1, const void * p2);
int compareOwner (const void * p1, const void * p2);
int compareMileage (const void * p1, const void * p2);
int compareYear (const void * p1, const void * p2);
void callSort (listManager * list);

#endif /* sortDatabase_h */
