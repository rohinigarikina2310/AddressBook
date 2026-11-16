#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  
    printf("inside savecontact\n");
    FILE *fptr = fopen("contacts.txt", "w");
    printf("contactCount = %d\n", addressBook->contactCount);
    if(fptr == NULL)
    {
        printf("unable to open\n");
    }
    fprintf(fptr, "#%d\n", addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("Contact saved succesfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.txt", "r");
    if(fptr ==NULL)
    {
        return;
    }
    fscanf(fptr,"#%d\n", &addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr ,"%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
