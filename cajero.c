/*This program is a simulation of a software that could be implemented in an ATM
 * Version 1.0*/

#include <stdio.h>
#include "user.h"
#include "prot.h"
#define MAX 10

int main(){
    int option=0, SN=1001;
    struct ent user[1];
    while(option!=3){
        printf("------Welcome to the ATM------\n");
        printf("1. Login\n");
        printf("2. Info\n");
        printf("3. Exit\n");
        printf("------------------------------\n");
        printf("Please choose an option: ");
        scanf("%i", &option);
        switch(option){
            case 1:
                printf("Logging in...\n");
                login(user);
                break;
            case 2:
                printf("Info:\n");
                printf("Machine serial number: %i\n", SN);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            }
    }
    return 0;
}

void login(struct ent user[]){
    int var=0, pass= 0;
    printf("Type your user ID or type (1) to create a new account\n");
    printf("ID: ");
    scanf("%i", &var);
    if(var==1){
        newaccount(user);
    }else if(var==user[0].id){
        printf("Password: ");
        scanf("%i", &pass);
        if(pass==user[0].password){
            printmenu(user);
        }
    }else{
        printf("Invalid ID, please contact support if the problem continues\nReturning to home menu...\n");
    }
}

void newaccount(struct ent user[]){
    int option=0;
    printf("------Welcome to the New User Configuration------\n");
    printf("1. Continue\n");
    printf("2. Cancel\n");
    printf("Do you wish to continue? ");
    scanf("%i", &option);
    if(option==1){
        printf("Choose an ID (between 1000 and 9999): ");
        scanf("%i", &user[0].id);
        printf("Choose a password (between 1000 and 9999): ");
        scanf("%i", &user[0].password);
        printf("Enter your name: ");
        scanf(" %[^\n]", &user[0].name);
        user[0].balance=0;
        printf("New user created, loging in...\n");
        printmenu(user);
    }else{
        printf("[CANCELED] Returning to home menu...\n");
    }
}

void printmenu(struct ent user[]){
    int option=0;
    while(option!=3){
        printf("------Welcome User: %s------\n", user[0].name);
        printf("ID: %i\n", user[0].id);
        printf("Current balance: $%f\n", user[0].balance);
        printf("---------------------------------------\n");
        printf("1. Edit balance\n");
        printf("2. User settings\n");
        printf("3. Logut\n");
        printf("Choose an action: ");
        scanf("%i", &option);
        switch(option){
            case 1:
                balance(user);
                break;
            case 2:
                usersettings(user);
                break;
            case 3:
                printf("Loging out...\n");
                break;
            }
    }
}

void balance(struct ent user[]){
    int option=0;
    float cuant=0;
    printf("------Account Balance------\n");
    printf("Current balance: $%f\n", user[0].balance);
    printf("1. Add to balance\n");
    printf("2. Remove from balance\n");
    printf("3. Cancel\n");
    printf("---------------------------\n");
    printf("Choose an action: ");
    scanf("%i", &option);
    switch(option){
        case 1:
            printf("ADD TO BALANCE\n");
            printf("Set an amount to add: $");
            scanf("%f", &cuant);
            printf("--------------\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Add %f?", cuant);
            scanf("%i", &option);
            if(option==1){
                user[0].balance+=cuant;
                printf("Ammount added\n");
            }else{
                printf("Transaction cancelled\n");
            }
            break;
        case 2:
            printf("REMOVE FROM BALANCE\n");
            printf("Set an amount to remove: $");
            scanf("%f", &cuant);
            printf("-------------------\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Remove %f?\n", cuant);
            scanf("%i", &option);
            if(option==1){
                if((user[0].balance-cuant)>=0){
                    user[0].balance-=cuant;
                    printf("Ammount removedn\n");
                }else{
                    printf("Error: can't leave the account in negatves\n");
                }
            }else{
                printf("Transaction cancelled\n");
            }
            break;
        case 3:
            printf("[CANCELLED] Returning to acount...\n");
            break;
    }
}

void usersettings(struct ent user[]){
    int option=0,temp;
    printf("------User Settings------\n");
    printf("1. Change ID\n");
    printf("2. Change password\n");
    printf("3. Remove account\n");
    printf("4. Cancel\n");
    printf("Choose an action: ");
    scanf("%i", &option);
    switch(option){
        case 1:
            printf("ID CHANGE\n");
            printf("Please type your current ID: ");
            scanf("%i", &temp);
            if(temp==user[0].id){
                printf("Please type your new id (between 1000 to 9999): ");
                scanf("%i", &temp);
                printf("---------------------\n");
                printf("1. Yes\n");
                printf("2. No\n");
                printf("Change id? ");
                scanf("%i", &option);
                if(option==1){
                    user[0].id=temp;
                    printf("ID changed\n");
                }else{
                    printf("Operation cancelled\n");
                }
            }else{
                printf("Error: IDs dont match\n");
            }
            break;
        case 2:
            printf("PASSWORD CHANGE\n");
            printf("Please type your current password: ");
            scanf("%i", &temp);
            if(temp==user[0].password){
                printf("Please type your new password (between 1000 to 9999): ");
                scanf("%i", &temp);
                printf("---------------------\n");
                printf("1. Yes\n");
                printf("2. No\n");
                scanf("%i", &option);
                if(option==1){
                    user[0].password=temp;
                    printf("Password changed\n");
                }else{
                    printf("Operation cancelled\n");
                }
            }else{
                printf("Error: Passwords don't match\n");
            }
            break;
        case 3:
            printf("REMOVE ACCOUNT\n");
            printf("1. Remove acount\n");
            printf("2. Cancel\n");
            printf("(WARNING account removal can't be un-donde, contact support for more information)\nChoose an action: ");
            scanf("%i", &option);
            if(option==1){
                printf("Please type yout password: ");
                scanf("%i", &temp);
                if(temp==user[0].password){
                    printf("Removing user...\n");
                    user[0].id=0;
                    printf("ID removed...\n");
                    user[0].password=0;
                    printf("Password removed...\n");
                    user[0].balance=0;
                    printf("Balanced removed...\n");
                    for(int i=0; i<= 40; i++){
                        user[0].name[i]='\0';
                    }
                    printf("Name removed...\n");
                    user[0].usage=0;
                    printf("User removed\n");
                }else{
                    printf("Error: password don't match\n");
                }
            }else{
                printf("[CANCELLED] Retunrning to account...\n");
            }
            break;
        case 4:
            printf("[CANCELLED] Returning to account...\n");
            break;
    }
}
