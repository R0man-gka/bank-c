#include <stdio.h>
#include <string.h>
#include "Bank.h"


void deposit(struct User *user){
    int pl;
    printf("Введите сумму пополнения:\n ");
    scanf("%d",&pl);
    user->acct.balance += pl;
    printf("Balance: %d\n", user->acct.balance);
}

void withdraw(struct User *user){
    int sl;
    printf("Ввидите сумму которую хотите снять:\n");
    scanf("%d",&sl);
    if (sl > user->acct.balance) {
    printf("Не достаточно средств!\n");
    }
    else user->acct.balance -= sl;
    printf("Balance: %d\n", user->acct.balance);
}

void account_info(struct Account acct){
    printf("Счёт: %s\n", acct.name);
    printf("Id: %d\n", acct.id);
    printf("------------------------\n");
    printf("Balance: %d\n", acct.balance);
    switch (acct.type) {
        case 1: printf("Type: SAVINGS\n"); break;
        case 2: printf("Type: CHECKING\n"); break;
        case 3: printf("Type: SOCIAL\n"); break;
    }
    
}

void account_create(struct Account *acct, int id){
    acct->id = id;
    acct->balance = 0;   
    printf("Ввидите имя счёта:\n");
    scanf("%s", acct->name);
    printf("Какой тип счёта (SAVINGS-1, CHECKING-2, SOCIAL-3):\n");
    scanf("%d", &acct->type);
}
void bank_account_create(struct User *user){
    printf("Придумайте Login:\n");
    scanf("%s", user->bank_info.login);
    printf("Введите pin-code:\n");
    scanf("%d", &user->bank_info.pin_code);

    account_create(&user->acct, 1);

    FILE *f = fopen(ACCOUNTS_FILE, "ab");
    fwrite(user, sizeof(struct User), 1, f);
    fclose(f);
}
void save_user_changes(struct User *user){
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    struct User temp;
    long pos;
    int found = 0;
    while (1){
        pos = ftell(f);                              // запоминаем позицию ПЕРЕД чтением
        if (fread(&temp, sizeof(struct User), 1, f) != 1) break; // файл закончился

        if (strcmp(temp.bank_info.login, user->bank_info.login) == 0){
            found = 1;
            break;                                    // нашли нужную запись, позиция запомнена в pos
        }
    }
    fclose(f);
    if (found){
        FILE *f2 = fopen(ACCOUNTS_FILE, "r+b");        // открываем для чтения И записи
        fseek(f2, pos, SEEK_SET);                       // перемещаемся на позицию нужной записи
        fwrite(user, sizeof(struct User), 1, f2);        // затираем её новыми данными
        fclose(f2);
    }
}
int authorization(struct User *user){
    printf("Ввидите login:\n");
    scanf("%s", user->bank_info.login);
    printf("Ввидите pin-code:\n");
    scanf("%d", &user->bank_info.pin_code);

    struct User temp;
    FILE *f = fopen(ACCOUNTS_FILE, "rb");

    while (fread(&temp, sizeof(struct User), 1, f)== 1){
        if (strcmp(temp.bank_info.login, user->bank_info.login) == 0 &&
            temp.bank_info.pin_code == user->bank_info.pin_code){
            user->acct = temp.acct;   
            fclose(f);
            return 1;
        }
    }
    printf("Аккаунт не найден\n");
    fclose(f); 
    return 0;
}