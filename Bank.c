#include <stdio.h>
#include <string.h>
#include "Bank.h"

void deposit(struct User *user, int idx){
    int pl;
    printf("Введите сумму пополнения:\n ");
    scanf("%d", &pl);
    user->accounts[idx].balance += pl;
    printf("Balance: %d\n", user->accounts[idx].balance);
}

void withdraw(struct User *user, int idx){
    int sl;
    printf("Введите сумму которую хотите снять:\n");
    scanf("%d", &sl);
    if (sl > user->accounts[idx].balance){
        printf("Не достаточно средств!\n");
    }
    else {
        user->accounts[idx].balance -= sl;
    }
    printf("Balance: %d\n", user->accounts[idx].balance);
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
    printf("Введите имя счёта:\n");
    scanf("%s", acct->name);
    printf("Какой тип счёта (SAVINGS-1, CHECKING-2, SOCIAL-3):\n");
    scanf("%d", &acct->type);
}

int bank_account_create(struct User *user){
    user->accounts_count = 0;   

    printf("Придумайте Login:\n");
    scanf("%s", user->bank_info.login);

    struct User temp;
    FILE *f = fopen(ACCOUNTS_FILE, "rb");

    if (f != NULL){
        while (fread(&temp, sizeof(struct User), 1, f) == 1){
            if (strcmp(temp.bank_info.login, user->bank_info.login) == 0){
                printf("Аккаунт с таким логином уже существует.\n");
                fclose(f);
                return 1;
            }
        }
        fclose(f);
    }

    printf("Введите pin-code:\n");
    scanf("%d", &user->bank_info.pin_code);

    account_create(&user->accounts[user->accounts_count], user->accounts_count + 1);
    user->accounts_count++;

    FILE *r = fopen(ACCOUNTS_FILE, "ab");
    fwrite(user, sizeof(struct User), 1, r);
    fclose(r);
    return 0;
}

void save_user_changes(struct User *user){
    FILE *f = fopen(ACCOUNTS_FILE, "rb");
    struct User temp;
    long pos;
    int found = 0;
    while (1){
        pos = ftell(f);                              
        if (fread(&temp, sizeof(struct User), 1, f) != 1) break; // файл закончился

        if (strcmp(temp.bank_info.login, user->bank_info.login) == 0){
            found = 1;
            break;                                    
        }
    }
    fclose(f);
    if (found){
        FILE *f2 = fopen(ACCOUNTS_FILE, "r+b");        
        fseek(f2, pos, SEEK_SET);                       
        fwrite(user, sizeof(struct User), 1, f2);        
        fclose(f2);
    }
}

int choice_account(struct User *user){
    printf("Выберите счёт:\n");
    for (int i = 0; i < user->accounts_count; i++){
        printf("%d. %s (баланс: %d)\n", i + 1, user->accounts[i].name, user->accounts[i].balance);
    }
    printf("0. Для создания нового счёта\n");
    printf("------------------------\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 0 && user->accounts_count < MAX_ACCOUNTS_PER_USER){
        account_create(&user->accounts[user->accounts_count], user->accounts_count + 1);
        user->accounts_count++;
        save_user_changes(user);
        return user->accounts_count - 1; 
    }
    else if (choice == 0 && user->accounts_count >= MAX_ACCOUNTS_PER_USER){
        printf("Достигнут лимит счетов для пользователя.\n");
        return -1; 
    }
    else if (choice < 1 || choice > user->accounts_count){
        printf("Неверный выбор.\n");
        return -1; 
    }

    return choice - 1;   
}

int authorization(struct User *user){
    printf("Введите login:\n");
    scanf("%s", user->bank_info.login);
    printf("Введите pin-code:\n");
    scanf("%d", &user->bank_info.pin_code);

    struct User temp;
    FILE *f = fopen(ACCOUNTS_FILE, "rb");

    while (fread(&temp, sizeof(struct User), 1, f)== 1){
        if (strcmp(temp.bank_info.login, user->bank_info.login) == 0 &&
            temp.bank_info.pin_code == user->bank_info.pin_code){
            *user = temp;
            fclose(f);
            return 1;
        }
    }
    printf("Аккаунт не найден\n");
    fclose( f); 
    return 0;
}

void menu(struct User *user, int idx){
    int b = 0;
    printf("1-Пополнить / 2-Снять / 3-Выход\n");
    scanf("%d", &b);
    switch (b) {
        case 1: deposit(user,idx); break;
        case 2: withdraw(user,idx); break;
        case 3: return;
    }
}