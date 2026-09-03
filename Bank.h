#ifndef BANK_H
#define BANK_H
#define ACCOUNTS_FILE "accounts.dat"
#define MAX_ACCOUNTS_PER_USER 5

struct Bank_account{
    char login[50];
    int pin_code;
};

enum account_type {
    SAVINGS = 1,
    CHECKING,
    SOCIAL,
};

struct Account {
    char name[50];
    int id;
    int balance;
    enum account_type type;
};

struct User {
    struct Bank_account bank_info;
    struct Account accounts[MAX_ACCOUNTS_PER_USER];
    int accounts_count;
};

void deposit(struct User *user, int idx);
void withdraw(struct User *user, int idx);
void account_info(struct Account acct);
int bank_account_create(struct User *user);
void account_create(struct Account *acct, int id);
void save_user_changes(struct User *user);
int choice_account(struct User *user);
int authorization(struct User *user);



#endif