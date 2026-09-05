#include <stdio.h>
#include "Bank.h"
#include <windows.h>


int main (void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int a = 0;
    
    struct User user;

    printf("Здравствуйте.\nУ вас есть учетная запись? (1-Да / 2-Нет)\n");
    scanf("%d", &a);
    printf("------------------------\n");
    
    if (a == 1) {
    int ok = authorization(&user);
    if (ok == 1){
        int idx = choice_account(&user);
        if (idx == -1){
        return 0;   
        }
        printf("------------------------\n");
        int exit = 0;
        while (exit == 0){
            exit = menu(&user,idx);
            save_user_changes(&user);
        }
    }
}
    if (a == 2) {
        int no = bank_account_create(&user);
        if (no == 1){
            return 0;
        }
        printf("------------------------\n");
        int idx = 0;
        int exit = 0;
        while (exit == 0){
            account_info(user.accounts[idx]);
            printf("------------------------\n");
            exit = menu(&user,idx);
            save_user_changes(&user);
        }
        
        
    }
    return 0;
}

