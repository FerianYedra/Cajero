/*This program is a simulation of a software that could be implemented in an ATM
 * Version 2.0*/

#include <stdio.h>
#include "user.h"
#include "cajero.h"
#define MAX 10

int main(int argc, char *argv[]){
    int option=0, SN=1001;
    struct ent user[1];

    if (argv[1][0]=='a'){
        admin();
    }

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
    int id=0, pass= 0;
    FILE *fp;
    char file[6];
    printf("Type your user ID or type (1) to create a new account\n");
    printf("ID: ");
    scanf(" %i", &id);
    if(id!=1){
        sprintf(file,"%i",id);
        fp=fopen(file,"r");
        fscanf(fp,"%i",&user[0].id);
        fclose(fp);
    }else if(id==1){
        newaccount(user);
    }
    if(id==user[0].id){
        loadfile(user);
        printf("Password: ");
        scanf(" %i", &pass);
        if(pass==user[0].password){
            printmenu(user);
        }
    }else{
        printf("Invalid ID, please contact support if the problem continues\nReturning to home menu...\n");
    }
}

void newaccount(struct ent user[]){
    int option=0,id;
    FILE *fp;
    printf("------Welcome to the New User Configuration------\n");
    printf("1. Continue\n");
    printf("2. Cancel\n");
    printf("Do you wish to continue? ");
    scanf("%i", &option);
    if(option==1){
        printf("Generating ID...\n");
        fp=fopen("IDdata.txt","r");
        fscanf(fp,"%i", &id);
        fclose(fp);
        id++;
        user[0].id=id;
        fp=fopen("IDdata.txt","w");
        fprintf(fp,"%i",id);
        fclose(fp);
        printf("ID generated succesfully: %i\n",id);
        printf("Choose a password (between 1000 and 9999): ");
        scanf("%i", &user[0].password);
        printf("Enter your name: ");
        scanf(" %[^\n]", user[0].name);
        user[0].balance=0;
        user[0].usage=1;
        printf("New user created, loging in...\n");
        writechanges(user);
        printmenu(user);
    }else{
        printf("[CANCELED] Returning to home menu...\n");
    }
}

void printmenu(struct ent user[]){
    int option=0;
    while(option!=3){
        printf("\n------Welcome User: %s------\n", user[0].name);
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
    writechanges(user);
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
    writechanges(user);
}

void admin(){
    int tempass, adminpass=1234;

    printf("Runnning in admin mode...\n");
    printf("Password: ");
    scanf("%i", &tempass);
    if (tempass==adminpass){
        printf("Loging in as admin...\n");
        printf("Admin still not available\n");
    }
}

int writechanges(struct ent user[]){
    FILE *fp;
    char tempid[6];
    printf("Saving changes...\n");
    sprintf(tempid,"%i",user[0].id);
    fp=fopen(tempid,"w");
    if (fp==NULL){
        printf("ERROR: Saving failed\n");
        return 1;
    }
    fprintf(fp,"%i\n",user[0].id);
    fprintf(fp,"%s\n",user[0].name);
    fprintf(fp,"%i\n",user[0].password);
    fprintf(fp,"%f\n",user[0].balance);
    fprintf(fp,"%i\n",user[0].usage);
    fclose(fp);
    printf("Chages saved\n");
    return 0;
}
void loadfile(struct ent user[]){
    FILE *fp;
    char tempid[6];
    printf("Loading files...\n");
    sprintf(tempid,"%i",user[0].id);
    fp=fopen(tempid,"r");
    fscanf(fp,"%i\n",&user[0].id);
    fscanf(fp,"%[^\n]\n",user[0].name);
    fscanf(fp,"%i\n",&user[0].password);
    fscanf(fp,"%f\n",&user[0].balance);
    fscanf(fp,"%i\n",&user[0].usage);
    printf("Files loaded\n");
    fclose(fp);
}
