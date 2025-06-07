#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "1234"

struct Contact {
    char name[30];
    char phone[20];
    char email[40];
};

int login();
void addrecord();
void listrecord();
void searchrecord();
void deleterecord();
void countrecord();
void pause();
void printLine();
void printHeader(const char* title);

int main() 
{
    if (!login())
    {
        printf("\n\n\t\t �α��� ����! ���α׷��� �����մϴ�.\n");
        return 0;
    }

    int choice;
    while (1)
    {
        printHeader(" ��ȭ��ȣ�� ���α׷�");
        printf("1. ����ó �߰�\n");
        printf("2. ����ó ��� ����\n");
        printf("3. ����ó �˻� (�̸� �Ϻ�)\n");
        printf("4. ����ó ����\n");
        printf("5. ��ü ����ó �� Ȯ��\n");
        printf("6. ����\n");
        printf("\n����: ");

        scanf("%d", &choice);
        getchar(); // ���� ����

        switch (choice) 
        
        {
        case 1: addrecord(); break;
        case 2: listrecord(); break;
        case 3: searchrecord(); break;
        case 4: deleterecord(); break;
        case 5: countrecord(); break;
        case 6:
            printf("\n ���α׷��� �����մϴ�.\n");
            return 0;
        default: printf(" �߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
        pause();
    }
    return 0;
}

int login() {
    char input[20];
    int tries = 0;

    printHeader(" �α��� ȭ��");

    while (tries < 3) {
        printf("��й�ȣ�� �Է��ϼ���: ");
        scanf("%s", input);

        if (strcmp(input, PASSWORD) == 0) return 1;

        printf(" ��й�ȣ�� Ʋ�Ƚ��ϴ�. ���� �õ�: %d\n", 2 - tries);
        tries++;
    }
    return 0;
}

void addrecord() {
    FILE* fp = fopen("phonebook.txt", "a");
    struct Contact c;

    printHeader(" ����ó �߰�");

    printf("�̸�: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("��ȭ��ȣ: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("�̸���: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    printf("\n ����Ǿ����ϴ�!\n");
}

void listrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    int count = 0;

    printHeader(" ����ó ���");

    while (fread(&c, sizeof(c), 1, fp)) {
        printf("�̸�: %s\n��ȭ: %s\n�̸���: %s\n------------------\n", c.name, c.phone, c.email);
        count++;
    }

    if (count == 0)
        printf(" ����� ����ó�� �����ϴ�.\n");

    fclose(fp);
}

void searchrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    char search[30];
    int found = 0;

    printHeader(" ����ó �˻�");

    printf("ã�� ���� �̸� �Ϻθ� �Է��ϼ���: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    printf("\n �˻� ���:\n");

    while (fread(&c, sizeof(c), 1, fp))
    {
        if (strstr(c.name, search))
        {
            printf("�̸�: %s\n��ȭ: %s\n�̸���: %s\n------------------\n", c.name, c.phone, c.email);
            found = 1;
        }
    }

    if (!found)
        printf(" '%s' �� ���Ե� ����ó�� ã�� �� �����ϴ�.\n", search);

    fclose(fp);
}

void deleterecord() 
{
    FILE* fp = fopen("phonebook.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    struct Contact c;
    char del[30];
    int found = 0;

    printHeader(" ����ó ����");

    printf("������ �̸��� �Է��ϼ���: ");
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
        printf(" '%s' ����ó�� �����Ǿ����ϴ�.\n", del);
    else
        printf(" ����ó�� ã�� �� �����ϴ�.\n");
}

void countrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    int count = 0;

    printHeader(" ��ü ����ó �� Ȯ��");

    if (fp == NULL) 
    {
        printf(" ������ �� �� �����ϴ�.\n");
        return;
    }

    while (fread(&c, sizeof(c), 1, fp)) 
    {
        count++;
    }
    fclose(fp);

    if (count == 0)
    {
        printf(" ����� ����ó�� �����ϴ�.\n");
    }
    else {
        printf("�� %d���� ����ó�� ����Ǿ� �ֽ��ϴ�.\n", count);
    }
}

void pause() 
{
    printf("\nEnter Ű�� ���� ����Ϸ���...\n");
    getchar();
}

void printLine() 
{
    printf("========================================\n");
}

void printHeader(const char* title)
{
    system("cls"); 
    printLine();
    printf("%s\n", title);
    printLine();
}
