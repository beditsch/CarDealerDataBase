//
//  fileWrite.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 31/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef fileWrite_h
#define fileWrite_h

#include <stdio.h>
#include "dataBaseElManager.h"
#include "userInterface.h"
#include <stdlib.h>
#include <string.h>
#include "fileRead.h"
#include "makeArrayManager.h"

void writeFile(char ** makesArray, listManager * list, FILE * fp);

#endif /* fileWrite_h */
