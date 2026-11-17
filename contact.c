#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

int foundindex = -1;
int matchedindex[100];
int matchcount;
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int i;
    if(addressBook->contactCount == 0)
    {
        printf("Not Avaliable\n");
        return;
    }
    printf("-------------------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-30s\n",
       "S.No","Name","Phone","E-mail");
    printf("-------------------------------------------------------------\n");
    for(i = 0;i<addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    printf("------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int isphoneUnique(AddressBook *addressBook, char *phone)
{
    int i;
    for(i =0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int isemailunique(AddressBook *addressBook, char *email)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Inside createContact\n");
    int i, j, valid, attempts = 0;
    i = addressBook->contactCount;
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the name: ");
        scanf(" %49[^\n]", addressBook->contacts[i].name);
        for(j =0; addressBook->contacts[i].name[j] != '\0'; j++)
        {
            if(!isalpha((unsigned char)addressBook->contacts[i].name[j]) && addressBook->contacts[i].name[j] !=' ')
            {
                valid = 0;
                break;
            }
        }
        if(valid == 1)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid name . Enter again\n");
        }
    }
    if(attempts == 3)
    {
        printf("maximum attempts reached\n");
        return;
    }

    attempts = 0;
    char phone[20];
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the phone number:");
        scanf("%10s", phone);
        if(strlen(phone) != 10)
        {
            valid = 0;
        }
        if(valid && !(phone[0] >='6' &&  phone[0] <= '9'))
        {
            valid = 0;
        }
        for(j=0; phone[j] != '\0'; j++)
        {
            if( !isdigit((unsigned char)phone[j]))
            {
                valid = 0;
                break;
            }
        }
        if(!isphoneUnique(addressBook,phone))
        {
            printf("phone number is already exists\n");
            valid = 0;
        }
        if(valid)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid phone number.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
    strcpy(addressBook->contacts[i].phone, phone);
    attempts = 0;
    char email[50];
    int emailLen;
    int atCount;
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the Email id:");
        scanf(" %49s", email);
        emailLen = strlen(email);
        atCount = 0;
        if(email[0] <'a' || email[0]>'z')
        {
            valid = 0;
        }
        for(j=0; email[j] != '\0'; j++)
        {
            if(email[j] == '@')
            {
                atCount++;
            }
        }
        if(atCount != 1)
        {
            valid = 0;
        }
        if(emailLen < 5 || strcmp(email + emailLen -4, ".com") != 0)
        {
            valid = 0;
        }
        if(!isemailunique(addressBook, email))
        {
            printf("Email is already exist\n");
            valid = 0;
        }
        if(valid == 1)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid email.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
    strcpy(addressBook->contacts[i].email, email);
    if(valid)
    {
        addressBook->contactCount++;
        printf("contact created successfully\n");
    }
}

void searchByname(AddressBook *addressBook)
{
    int j ,valid, attempts = 0;
    char name[100];
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the name:");
        scanf(" %49[^\n]", name);
        for(j =0; name[j] !='\0';j++)
        {
            if(!isalpha((unsigned char)name[j]) && name[j] !=' ')
            {
                valid = 0;
                break;
            }
        }    
        if(valid)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid enter again\n");
        }
    }
    if(attempts == 3)
    {
        printf("maximum attempts reached\n");
        return;
    }
    int found = 0;
    printf("-------------------------------------------------------------\n");
     printf("%-5s %-20s %-15s %-30s\n","S.No","Name","Phone","E-mail");
    printf("-------------------------------------------------------------\n");


    for(int i=0; i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,name) == 0)
        {
            found = 1;
            foundindex = i;
            matchedindex[matchcount] = i;
            printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            matchcount++;
        }
    }
    printf("-------------------------------------------------------------\n");
    if(found ==0)
    {
        printf("conatct is not found\n");
        return ;
    }
}
void searchByphone(AddressBook *addressBook)
{
    int j, valid, attempts = 0;
    char phone[20];
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the phone number:");
        scanf("%10s", phone);
        if(strlen(phone) != 10)
        {
            valid = 0;
        }
        if(valid && !(phone[0] >='6' &&  phone[0] <= '9'))
        {
            valid = 0;
        }
        for(j=0; phone[j] != '\0'; j++)
        {
            if( !isdigit((unsigned char)phone[j]))
            {
                valid = 0;
                break;
            }
        }
        if(valid)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid phone number.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
        int found = 0;
        for(int i=0; i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone) == 0)
            {
                found = 1;
                foundindex = i;
                printf("contact found\n");
                printf("Name: %s\n",addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("E-mail: %s\n",addressBook->contacts[i].email);
                break;
            }
        }
        if(found ==0)
        {
            printf("conatct is not found\n");
            return ;
        }
}
void searchByemail(AddressBook *addressBook)
{
    int valid, j, attempts = 0;
    char email[50];
    int emailLen;
    int atCount;
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the Email id:");
        scanf(" %49s", email);
        emailLen = strlen(email);
        atCount = 0;
        if(email[0] <'a' || email[0]>'z')
        {
            valid = 0;
        }
        for(j=0; email[j] != '\0'; j++)
        {
            if(email[j] == '@')
            {
                atCount++;
            }
        }
        if(atCount != 1)
        {
            valid = 0;
        }
        if(emailLen < 5 || strcmp(email + emailLen -4, ".com") != 0)
        {
            valid = 0;
        }

        if(valid == 1)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid email.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
    int found = 0;
    for(int i=0; i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
        {
            found = 1;
            foundindex = i;
            printf("contact found\n");
            printf("Name: %s\n",addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("E-mail: %s\n",addressBook->contacts[i].email);
            break;
        }
    }
    if(found == 0)
    {
        printf("conatct is not found\n");
        return ;
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    printf("\n1.search by name:");
    printf("\n2.search by phone:");
    printf("\n3.search by e-mail:");
    printf("\n4.exsit");
    printf("\nEnter the choice:");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            searchByname(addressBook);
            break;
        case 2:
            searchByphone(addressBook);
            break;
        case 3:
             searchByemail(addressBook);
             break;
        case 4:
            return;
        default:
           printf("invalid\n"); 
    }
}

int searchbyindex(AddressBook *addressBook)
{
    char phone[20];
    printf("enter the phone:");
    scanf("%s", phone);
    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone))
        {
            return i;
        }
    }
    return -1;
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	matchcount = 0;
    foundindex = -1;
    int choice;
    searchContact(addressBook);
	if(matchcount == 1)
    {
        foundindex = matchedindex[0];
    }
    else if(matchcount > 1)
    {
        int sno;
        printf("enter the serial number:");
        scanf("%d", &sno);
        if(sno < 1 || sno > matchcount)
        {
            printf("invalid serial number");
            return;
        }
        foundindex = matchedindex[sno - 1];
    }
    if(foundindex == -1)
    {
        printf("contact not found");
        return;
    }
    printf("Contact found\n");
    printf("\nEdit contact\n");
    printf("1.edit name");
    printf("\n2.edit phone number");
    printf("\n3.edit E-mail");
    printf("\nEnter the choice:");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        int i, j, valid, attempts = 0;
        while(attempts < 3)
        {
            valid = 1;
            printf("Enter the new name:");
            scanf(" %49[^\n]",addressBook->contacts[foundindex].name);
            for(j =0; addressBook->contacts[foundindex].name[j] != '\0'; j++)
            {
                if(!isalpha((unsigned char)addressBook->contacts[foundindex].name[j]) && addressBook->contacts[foundindex].name[j] !=' ')
                {
                    valid = 0;
                    break;
                }
            }
            if(valid == 1)
            {
                break;
            }
            else
            {
                attempts++;
                printf("Invalid name . Enter again\n");
            }
        }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
        break;
    case 2:
        attempts = 0;
    char phone[20];
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the phone number:");
        scanf(" %10s", phone);
        if(strlen(phone) != 10)
        {
            valid = 0;
        }
        if(valid && !(phone[0] >='6' &&  phone[0] <= '9'))
        {
            valid = 0;
        }
        for(j=0; phone[j] != '\0'; j++)
        {
            if( !isdigit((unsigned char)phone[j]))
            {
                valid = 0;
                break;
            }
        }
        if(!isphoneUnique(addressBook,phone))
        {
            printf("phone number is already exists\n");
            valid = 0;
        }
        if(valid)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid phone number.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
    strcpy(addressBook->contacts[foundindex].phone, phone);
        break;
    case 3:
        attempts = 0;
    char email[50];
    int emailLen;
    int atCount;
    while(attempts < 3)
    {
        valid = 1;
        printf("Enter the Email id:");
        scanf(" %49s", email);
        emailLen = strlen(email);
        atCount = 0;
        if(email[0] <'a' || email[0]>'z')
        {
            valid = 0;
        }
        for(j=0; email[j] != '\0'; j++)
        {
            if(email[j] == '@')
            {
                atCount++;
            }
        }
        if(atCount != 1)
        {
            valid = 0;
        }
        if(emailLen < 5 || strcmp(email + emailLen -4, ".com") != 0)
        {
            valid = 0;
        }
        if(!isemailunique(addressBook, email))
        {
            printf("Email is already exist\n");
            valid = 0;
        }
        if(valid == 1)
        {
            break;
        }
        else
        {
            attempts++;
            printf("Invalid email.enter again\n");
        }
    }
        if(attempts == 3)
        {
            printf("maximum attempts reached\n");
            return;
        }
        strcpy(addressBook->contacts[foundindex].email, email);
        break;
    case 4:
        return;
    default:
        printf("invalid choice\n");
        break;
    }
    printf("succesffully changed contact");

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char name[50];
    
    int sno;
    int choice, i;

    printf("\nDelete the contact\n");
    printf("\n1.delete by name");
    printf("\n2.Delete by phone");
    printf("\n3.Delete by e-mail");
    printf("\nenter the choice:");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("Enter the name: ");
            scanf(" %49[^\n]", name);
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    matchedindex[matchcount] = i;

                    printf("%d\t%s\t%s\t%s\n",
                           matchcount + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    matchcount++;
                }
            }

            if(matchcount == 0)
            {
                printf("Contact not found\n");
                return;
            }

            printf("Enter serial number to delete: ");
            scanf("%d", &sno);

            if(sno < 1 || sno > matchcount)
            {
                printf("Invalid serial number\n");
                return;
            }

            foundindex = matchedindex[sno - 1];
            break;

        case 2:

            searchByphone(addressBook);

            if(foundindex == -1)
            {
                printf("Contact not found\n");
                return;
            }
            break;

        case 3:

            searchByemail(addressBook);

            if(foundindex == -1)
            {
                printf("Contact not found\n");
                return;
            }
            break;

        default:
            printf("Invalid choice\n");
            return;
    }

    for(i = foundindex; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}
