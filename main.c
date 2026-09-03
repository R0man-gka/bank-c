#include <stdio.h>
#include "Bank.h"
#include <windows.h>


int main (void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int a = 0;
    int b = 0;
    struct User user;

    printf("Здравствуйте.\nУ вас есть учетная запись? (1-Да / 2-Нет)\n");
    scanf("%d", &a);
    printf("------------------------\n");
    
    if (a == 1) {
        int ok = authorization(&user);
        if (ok == 1){
            printf("------------------------\n");
            int idx = choice_account(&user);
            account_info(user.accounts[idx]);
            printf("------------------------\n");
            printf("1-Пополнить / 2-Снять / 3-Выход\n");
            scanf("%d", &b);
            switch (b) {
            case 1: deposit(&user,idx); break;
            case 2: withdraw(&user,idx); break;
            case 3: return 0;
            }
            save_user_changes(&user);
        }
    }
    if (a == 2) {
        bank_account_create(&user);
        printf("------------------------\n");
        int idx = 0;
        
        account_info(user.accounts[idx]);
        printf("------------------------\n");
        printf("1-Пополнить / 2-Снять / 3-Выход\n");
        scanf("%d", &b);
        switch (b) {
        case 1: deposit(&user,idx); break;
        case 2: withdraw(&user,idx); break;
        case 3: return 0;
        }   
        save_user_changes(&user);
    }
    return 0;
}