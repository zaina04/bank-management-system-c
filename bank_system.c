#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// Create account
void createAccount() {
    FILE *fp = fopen("accounts.txt", "a");

    struct Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf("%s", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n\n");
}

// Display accounts
void displayAccounts() {
    FILE *fp = fopen("accounts.txt", "r");

    struct Account acc;

    printf("\n--- Accounts ---\n");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n",
               acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
}

// Deposit
void deposit() {
    FILE *fp = fopen("accounts.txt", "r+");

    int accNo;
    float amount;
    struct Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("Deposit Successful!\n\n");
            break;
        }
    }

    fclose(fp);
}

// Withdraw
void withdraw() {
    FILE *fp = fopen("accounts.txt", "r+");

    int accNo;
    float amount;
    struct Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter Amount: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("Insufficient Balance!\n\n");
            } else {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("Withdrawal Successful!\n\n");
            }
            break;
        }
    }

    fclose(fp);
}

// Menu
int main() {
    int choice;

    do {
        printf("==== Bank Management System ====\n");
        printf("1. Create Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
