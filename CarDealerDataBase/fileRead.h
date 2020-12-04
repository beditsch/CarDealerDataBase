//
//  fileReadAndWrite.h
//  CarDealerDataBase
//
//  Created by Marcin Badach on 29/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#ifndef fileRead_h
#define fileRead_h


#include <stdio.h>

#include "dataBaseElManager.h"
#include "userInterface.h"
#include <stdlib.h>
#include <string.h>
#include "makeArrayManager.h"

char ** readPossibleMakes (FILE * sourceFile);
listManager * createElementsList (FILE * sourceFile);


#endif
