//
//  main.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 17/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "fileRead.h"
#include "userInterface.h"
#include "dataBaseElManager.h"
#include "sortDatabase.h"


int main(void) {
    
    FILE* sourceFile;
    
    puts("Marcin Badach, grupa: środy 14:15, baza salonu samochodowego.");
    sourceFile = openFile();

    char ** makesArray;
    makesArray = readPossibleMakes(sourceFile);
    listManager * list = createElementsList(sourceFile);

    fclose(sourceFile);
    
    puts("Wczytane marki:");
    
    printPossibleMakes(makesArray);
    
    puts("Wczytane pozycje w bazie:");
    
    printCarList(list);
    int status = 0;
    while ( (status = decideWhatToDo(sourceFile, makesArray, list)) ) {
        if (status == 1) {
        puts("Procedura zakończona!\n");
        puts("Marki do wyboru:");
        printPossibleMakes(makesArray);
        puts("Pozycje w bazie:");
        printCarList(list);
        }
        continue;
    }
    
    FILE * destinationFile = openSaveFile();
    writeFile(makesArray, list, destinationFile);
    fclose(destinationFile);
    
    cleanDataBase(makesArray, list);
    puts("Baza została zapisana do pliku!");
    
    
    return 0;
}





