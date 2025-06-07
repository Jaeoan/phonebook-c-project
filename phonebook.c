#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[30];
    char phone[20];
    char email[40];
};

void addrecord();
void listrecord();
void searchrecord();
void deleterecord();

int main() {
    int choice;
    while (1) {
        printf("\n===== Phonebook Menu =====\n");
        printf("1. Add Record\n");
        printf("2. List Records\n");
        printf("3. Search Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // 버퍼 비우기

        switch (choice) {
        case 1: addrecord(); break;
        case 2: listrecord(); break;
        case 3: searchrecord(); break;
        case 4: deleterecord(); break;
        case 5: exit(0);
        default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

void addrecord() {
    FILE* fp = fopen("phonebook.txt", "a");
    struct Contact c;

    printf("Enter Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;  // 줄바꿈 제거

    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    printf("Record added successfully!\n");
}

void listrecord() {
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    int count = 0;

    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n---\n", c.name, c.phone, c.email);
        count++;
    }

    if (count == 0) printf("No contacts found.\n");
    fclose(fp);
}

void searchrecord() {
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    char search[30];
    int found = 0;

    printf("Enter name to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, search) == 0) {
            printf("Record found!\nName: %s\nPhone: %s\nEmail: %s\n", c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }

    if (!found) printf("No contact found with that name.\n");
    fclose(fp);
}

void deleterecord() {
    FILE* fp = fopen("phonebook.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    struct Contact c;
    char del[30];
    int found = 0;

    printf("Enter name to delete: ");
    fgets(del, sizeof(del), stdin);
    del[strcspn(del, "\n")] = 0;

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, del) != 0) {
            fwrite(&c, sizeof(c), 1, temp);
        }
        else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");

    if (found)
        printf("Record deleted.\n");
    else
        printf("No contact found with that name.\n");
}
이거 깃허브에 코드 올리고 싶어