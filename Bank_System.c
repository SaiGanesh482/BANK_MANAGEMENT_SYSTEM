#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Transaction
{
    char type[50];
    int amount;
    int tx_id;   
};

struct Account
{
    int acc_no;
    char name[50];
    int balance;
    struct Account *next;

    struct Transaction T[5];

    int index;
    int count;
};

struct Account *head = NULL;

int GLOBAL_TX_ID = 1000;   

struct Account * create_node(int acc,char *n,int b)
{
    struct Account * nod = malloc(sizeof(struct Account));
    nod->acc_no = acc;
    strcpy(nod->name, n);
    nod->balance = b;
    nod->next = NULL;
    nod->index = 0;
    nod->count = 0;
    return nod;
}

struct Account * find(int acc)
{
    struct Account * temp = head;
    while(temp)
    {
        if(temp->acc_no == acc)
            return temp;

        temp = temp->next;
    }
    return NULL;
}

void addTransaction(struct Account * a,char *type,int bal)
{
    strcpy(a->T[a->index].type, type);
    a->T[a->index].amount = bal;
    a->T[a->index].tx_id = GLOBAL_TX_ID++;

    a->index = (a->index + 1) % 5;

    if(a->count < 5)
        a->count++;
}

void Add_Account()
{
    int acc;
    char name[50];
    int balance;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = find(acc);

    if(ptr != NULL)
    {
        printf("Account Already Exists\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    printf("Enter Initial Balance: ");
    scanf("%d", &balance);

    struct Account* node = create_node(acc, name, balance);

    if(head == NULL)
        head = node;
    else
    {
        struct Account *temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = node;
    }

    addTransaction(node, "Initial-Deposit", balance);

    printf("✔ Account Created Successfully!\n");
}


void Deposit()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = find(acc);
    if(ptr == NULL)
    {
        printf("Account Number Doesn't Exist\n");
        return;
    }

    int bal = 0;
    printf("Enter Amount to Deposit: ");
    scanf("%d", &bal);

    if (bal <= 0)
    {
        printf("Invalid Amount!\n");
        return;
    }

    ptr->balance += bal;

    addTransaction(ptr, "Deposit", bal);

    printf("✔ Deposit Successful!\n");
}


void Withdraw()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = find(acc);
    if(ptr == NULL)
    {
        printf("Account Number Doesn't Exist\n");
        return;
    }

    int bal = 0;
    printf("Enter Amount to Withdraw: ");
    scanf("%d", &bal);

    if (bal <= 0 || bal > ptr->balance)
    {
        printf("Invalid Amount!\n");
        return;
    }

    ptr->balance -= bal;

    addTransaction(ptr, "Withdrawal", bal);

    printf("✔ Withdrawal Successful!\n");
}


void Balace_Enq()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = find(acc);

    if(ptr == NULL)
    {
        printf("Account Doesn't Exist\n");
        return;
    }

    printf("\nAccount Number : %-5d | Name : %-15s | Balance : %-6d\n",
           ptr->acc_no, ptr->name, ptr->balance);
}

void Transfer()
{
    int frm_acc, to_acc;
    int bal;

    printf("\nEnter From Account Number: ");
    scanf("%d", &frm_acc);

    struct Account *A = find(frm_acc);
    if(A == NULL)
    {
        printf("Invalid Account Number\n");
        return;
    }

    printf("Enter To Account Number: ");
    scanf("%d", &to_acc);

    struct Account *B = find(to_acc);
    if(B == NULL)
    {
        printf("Invalid Account Number\n");
        return;
    }

    if(A == B)
    {
        printf("Cannot Transfer to the same Account\n");
        return;
    }

    printf("Enter Amount to Transfer: ");
    scanf("%d", &bal);

    if (A->balance < bal)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    A->balance -= bal;
    B->balance += bal;

    addTransaction(A, "Transfer-out", bal);
    addTransaction(B, "Transfer-in", bal);

    printf("✔ Transfer Successful!\n");
}

void show_Account()
{
    struct Account *temp = head;

    if(temp == NULL)
    {
        printf("No accounts to show.\n");
        return;
    }

    printf("\n-------------------- ACCOUNT LIST --------------------\n");

    while(temp != NULL)
    {
        printf("Account Number : %-5d | Name : %-15s | Balance : %-6d\n",
               temp->acc_no, temp->name, temp->balance);

        temp = temp->next;
    }
}


void Disp_Trans()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    struct Account *ptr = find(acc);

    if(ptr == NULL)
    {
        printf("Account Doesn't Exist\n");
        return;
    }

    if(ptr->count == 0)
    {
        printf("No Transactions Available\n");
        return;
    }

    printf("\nLast %d Transactions:\n", ptr->count);
    printf("---------------------------------------\n");

    int start = (ptr->index - ptr->count + 5) % 5;

    for(int i = 0; i < ptr->count; i++)
    {
        int pos = (start + i) % 5;
        printf("ID : %-5d | Type : %-15s | Amount : %-6d\n",
               ptr->T[pos].tx_id,
               ptr->T[pos].type,
               ptr->T[pos].amount);

    }
}

void Search_Account()
{
    int acc;
    printf("Enter Account Number: ");
    scanf("%d",&acc);

    struct Account *ptr = find(acc);

    if(ptr == NULL)
    {
        printf("Account Not Found\n");
        return;
    }

    printf("\nAccount Found:\n");
    printf("Account Number : %-5d | Name : %-15s | Balance : %-6d\n",
           ptr->acc_no, ptr->name, ptr->balance);
}


void Save_File()
{
    FILE *fp = fopen("bank.dat", "wb");
    if(fp == NULL)
    {
        printf("File save error!\n");
        return;
    }

    struct Account *temp = head;

    while(temp)
    {
        fwrite(temp, sizeof(struct Account), 1, fp);
        temp = temp->next;
    }

    fclose(fp);
    printf("✔ Data Saved Successfully!\n");
}

void Load_File()
{
    FILE *fp = fopen("bank.dat", "rb");
    if(fp == NULL)
        return;

    while(1)
    {
        struct Account temp;

        if(fread(&temp, sizeof(struct Account), 1, fp) != 1)
            break;

        struct Account *node = malloc(sizeof(struct Account));
        *node = temp;
        node->next = head;
        head = node;
    }

    fclose(fp);
}

int main()
{
    Load_File();

    int ch = 0;

    printf("\n===============================================================\n");
    printf("                    BANK MANAGEMENT SYSTEM                     \n");
    printf("===============================================================\n");

    while(1)
    {
        printf("\n--------------- MENU ---------------\n");
        printf(" 1. Add Account\n");
        printf(" 2. Show Accounts\n");
        printf(" 3. Deposit\n");
        printf(" 4. Withdraw\n");
        printf(" 5. Balance Enquiry\n");
        printf(" 6. Transfer\n");
        printf(" 7. Show Transactions\n");
        printf(" 8. Search Account\n");
        printf(" 9. Save Data\n");
        printf("10. Exit\n");
        printf("-------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: Add_Account(); break;
            case 2: show_Account(); break;
            case 3: Deposit(); break;
            case 4: Withdraw(); break;
            case 5: Balace_Enq(); break;
            case 6: Transfer(); break;
            case 7: Disp_Trans(); break;
            case 8: Search_Account(); break;
            case 9: Save_File(); break;

            case 10:
                Save_File();
                printf("\nThank you! Exiting...\n");
                return 0;

            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }

    return 0;
}
