//
//  dataBase.c
//  CarDealerDataBase
//
//  Created by Marcin Badach on 28/05/2019.
//  Copyright © 2019 Marcin Badach. All rights reserved.
//

#include "dataBaseElManager.h"



void cleanInput (void) {
    char ch;
    while( (ch = getchar()) != '\n')
        continue;
}

//funkcja, która po wczytaniu do text stringLength znaków sprawdza, czy w tekst znajduje się znak '\n' (jesli tak to zamienia do na '\0', a jeśli nie, to czyści dalsze wejście
void dealWithInputAndNewLine(char * text, int stringLength) {
    int i;
    for (i = stringLength - 1; i > 0; i--) {
        if ( text[i] == '\n' ) {
            text[i] = '\0';
            break;
        }
    }
    if (i == 0 && text[0] != '\n')
        cleanInput();
}



int requestMake (char ** makesList) {
    
    if (makesList == NULL)
        return -1;
    
    int selectedMake = 0;
    
    puts("Wybierz markę (wpisz odpowiednią cyfrę) :");
    printPossibleMakes(makesList);
    
    scanf("%d", &selectedMake);
    
    cleanInput();
    
    while (selectedMake > nOfDefMakes(makesList) || selectedMake < 1) {
        puts("To nie jest trudne. Wybierz poprawnie markę samochodu (wpisz odpowiednią cyfrę) :");
        printPossibleMakes(makesList);
        scanf("%d", &selectedMake);
        
        cleanInput();
    }
    return selectedMake;
}


static char * requestModel (void){
    char * model;
    model = malloc(25 * sizeof(char));
    puts("Podaj model samochodu:");
    
    fgets(model, 25, stdin);
    
    dealWithInputAndNewLine(model, 25);
    
    while ( (model)[0] == '\n' ||  (model)[0] == '\0' || model[0] == ' ') {
        puts("To nie jest trudne. Podaj poprawnie model samochodu:");
        fgets(model, 25, stdin);
        
        dealWithInputAndNewLine(model, 25);
    }
    
    return model;
}

static int requestYear (void) {
    int year;
    puts("Podaj rok produkcji samochodu:");
    while (scanf("%d", &year) != 1 || year > 2020 || year < 1900) {
        
        cleanInput();
        
        puts("To nie jest trudne. Podaj poprawny rok produkcji:");
    }
    return year;
}

static int requestMileage (void) {
    int mileage;
    puts("Podaj przebieg samochodu:");
    while (scanf("%d", &mileage) != 1 || mileage > 1000000 || mileage < 0) {
        
        cleanInput();
        
        puts("To nie jest trudne. Podaj poprawny przebieg:");
    }
    return mileage;
}


static int requestOwner (void) {
    int owner;
    puts("Podaj liczbę właścicieli samochodu:");
    while (scanf("%d", &owner) != 1 || owner > 100 || owner < 0) {
        
        cleanInput();
        
        puts("To nie jest trudne. Podaj poprawną liczbę właścicieli:");
    }
    return owner;
}

static int requestPrice (void) {
    int price;
    puts("Podaj cenę samochodu:");
    while (scanf("%d", &price) != 1 || price < 100) {
        
        cleanInput();
        
        puts("To nie jest trudne, podaj poprawną cenę samochodu:");
    }
    return price;
}



//funkcja dodająca nowy rekord do bazy
void addElement (listManager * listPointer, char ** makesArray) {
    if (listPointer == NULL)
        return;
    if (makesArray == NULL)
        return;

    if (nOfDefMakes(makesArray) == 0) {
        puts("Dodanie elementu niemożliwe. Zdefiniuj najpierw przynajmniej jedną markę.");
        return;
    }
    CAR * newEl = (CAR *)malloc(sizeof(CAR));
    newEl -> next = NULL;
    newEl -> previous = listPointer -> listTail;
    
    if(listPointer -> listTail == NULL) {
        listPointer -> listHead = newEl;
        listPointer -> listTail = newEl;
    }
    else {
        listPointer -> listTail -> next = newEl;
        listPointer -> listTail = newEl;
    }
    
    
    
    puts("Rozpoczynamy procedurę dodawania elementu.");
    int chosenMake = requestMake(makesArray);
    newEl -> make = (char *)malloc(25 * sizeof(char));
    strncpy(newEl -> make, chooseMake(makesArray, chosenMake), 25);
    
    newEl -> model = requestModel();
    newEl -> yearOfProduction = requestYear();
    newEl -> mileage = requestMileage();
    newEl -> owner = requestOwner();
    newEl -> price = requestPrice();
    
    cleanInput();
    return;
}

int findCurrentNumberOfElements (listManager * list) {
    int numberOfEl = 0;
    if (list == NULL)
        return 0;
    if(list -> listHead == NULL)
        return 0;
    
    CAR * carPointer = (list -> listHead);
    
    while(carPointer != NULL) {
        numberOfEl++;
        carPointer = carPointer -> next;
    }
    return numberOfEl;
}


//funkcja, która zwraza numer rekordu do usunięcia, number oznacza liczbę wszystkich rekordów, przez co funkcja może kontrolować czy podane ID rekordu do usunięcia jest poprawne.
static int requestIDforDeleting (int number) {
    int ID;
    puts("Podaj numer rekordu, który chcesz usunąć:");
    while (scanf("%d", &ID) != 1 || ID < 1 || ID > number) {
        
        cleanInput();
        
        puts("To nie jest trudne. Podaj poprawny numer rekordu:");
    }
    return ID;
}

static CAR * findSpecificElement (listManager * list, int ID) {
    if (list == NULL)
        return NULL;
    if (list -> listHead == NULL)
    return NULL;
    
    CAR * pointer;
    pointer = list -> listHead;
    int i;
    for (i = 2; i <= ID; i++) {
        pointer = pointer -> next;
    }
    return pointer;
}




void deleteElement (listManager * listPointer) {
    if (listPointer == NULL)
        return;
    if(listPointer -> listHead == NULL) {
        puts("Baza jest pusta. Usunięcie elementu niemożliwe.");
        return;
    }

    
    int numberOfEl = findCurrentNumberOfElements(listPointer);
    int IDtoDelete = requestIDforDeleting(numberOfEl);
    CAR * toDelete = findSpecificElement(listPointer, IDtoDelete);
    
    if (IDtoDelete != 1 && IDtoDelete != numberOfEl) {
        toDelete -> previous -> next = toDelete -> next;
        toDelete -> next -> previous = toDelete -> previous;
        free(toDelete);
    }
    else if (IDtoDelete == 1 && IDtoDelete == numberOfEl) {
        listPointer -> listTail = NULL;
        listPointer -> listHead = NULL;
        free(toDelete);
    }
    else if (IDtoDelete == 1) {
        listPointer -> listHead = toDelete -> next;
        toDelete -> next -> previous = NULL;
        free(toDelete);
    }
    else if (IDtoDelete == numberOfEl) {
        listPointer -> listTail = toDelete -> previous;
        toDelete -> previous -> next = NULL;
        free(toDelete);
    }
    cleanInput();
}



static int requestIDforEditing (int number) {
    int ID;
    puts("Podaj numer rekordu, który chcesz edytować:");
    while (scanf("%d", &ID) != 1 || ID < 1 || ID > number) {
        
        cleanInput();
        
        puts("Nie wygłupiaj się, podaj poprawny numer rekordu:");
    }
    return ID;
}

char whichFieldtoEdit (void) {
    char edit;
    puts("Które pole chcesz edytować? \n1 - marka, 2 - model, 3 - rok produkcji, 4 - przebieg, 5 - wlasciciel, 6 - cena;\nJeśli chcesz zakończyć - wciśnij k");
    edit = getchar();
    cleanInput();
    
    while (edit != '1' && edit != '2' && edit != '3' && edit != '4' && edit != '5' && edit != '6' && edit != 'k'){
        
        puts("Podałeś niepoprawny symbol, spróbuj ponownie.\n1 - marka, 2 - model, 3 - rok produkcji, 4 - przebieg, 5 - wlasciciel, 6 - cena;\nJeśli chcesz zakończyć - wciśnij k");
        edit = getchar();
        cleanInput();
    }
    
    return edit;
}


static void editMakeInEl (CAR * el, char ** makesArray) {
    int selectedMake;
    selectedMake = requestMake(makesArray);
    strncpy(el -> make, chooseMake(makesArray, selectedMake), 25);
    puts("Zmiana została wprowadzona pomyślnie!");
}

static void editModel (CAR * el){
    char * newModel;
    newModel = requestModel();
    free (el -> model);
    el -> model = newModel;
    puts("Zmiana została wprowadzona pomyślnie!");
}

static void editYear (CAR * el) {
    int newYear;
    newYear = requestYear();
    el -> yearOfProduction = newYear;
    cleanInput();
    puts("Zmiana została wprowadzona pomyślnie!");
}

static void editMileage (CAR * el) {
    int newMileage;
    newMileage = requestMileage();
    el -> mileage = newMileage;
    cleanInput();
    puts("Zmiana została wprowadzona pomyślnie!");
}
static void editOwner (CAR * el) {
    int newOwner;
    newOwner = requestOwner();
    el -> owner = newOwner;
    cleanInput();
    puts("Zmiana została wprowadzona pomyślnie!");
}
static void editPrice (CAR * el) {
    int newPrice;
    newPrice = requestPrice();
    el -> price = newPrice;
    cleanInput();
    puts("Zmiana została wprowadzona pomyślnie!");
}




//funkcja w zależności od c pozwala zedytować jedno z pól elementu el
void decideWhatToEdit (char c, CAR * el, char ** makesArray) {
    if (c == 'k') {
        cleanInput();
        return;
    }

    else if (c == '1')
        editMakeInEl(el, makesArray);
    else if (c == '2')
        editModel(el);
    else if (c == '3')
        editYear(el);
    else if (c == '4')
        editMileage(el);
    else if (c == '5')
        editOwner(el);
    else if (c == '6')
        editPrice(el);
}



void editElement (listManager * listPointer, char ** makesArray) {
    if (listPointer == NULL)
        return;
    if (listPointer -> listHead == NULL) {
        puts("Zdefiniuj rekord, aby móc go edytować.");
        return;
    }
    if (makesArray == NULL)
        return;
    
//    printCarList(listPointer);
    int numberOfEl = findCurrentNumberOfElements(listPointer);
    int IDtoEdit = requestIDforEditing(numberOfEl);
    CAR * toEdit = findSpecificElement(listPointer, IDtoEdit);
    
    cleanInput();
    
    char c, ch;
    c = whichFieldtoEdit();
    decideWhatToEdit(c, toEdit, makesArray);
    puts("\nOto uaktualniona baza rekordów: ");
    printCarList(listPointer);
    puts("Czy chcesz edytować kolejne pole tego elementu? Jeśli tak - wprowadź t, jeśli nie, naciśnic dowolny inny klawisz.");
    ch = getchar();
    cleanInput();
    
    while (ch == 't') {
        c = whichFieldtoEdit();
        
        decideWhatToEdit(c, toEdit, makesArray);
        puts("\nOto uaktualniona baza rekordów:");
        printCarList(listPointer);
        puts("Czy chcesz edytować kolejne pole tego elementu? Jeśli tak - wprowadź t, jeśli nie, naciśnic dowolny inny klawisz.");
        ch = getchar();
        cleanInput();
    }
}



void cleanDataBase (char ** makesArray, listManager * list) {
    if (list == NULL)
        return;
    int i;
    for (i = 0; i < 5; i++) {
        cleanString(makesArray[i], 25);
    }
    
    CAR * carPointer;
    CAR * temp;
    carPointer = list -> listHead;
    
    list -> listHead = NULL;
    list -> listTail = NULL;
    
    while (carPointer != NULL) {
        temp = carPointer;
        carPointer = carPointer -> next;
        free(temp);
    }
}
