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
        printf("\n\n\t\t 로그인 실패! 프로그램을 종료합니다.\n");
        return 0;
    }

    int choice;
    while (1)
    {
        printHeader(" 전화번호부 프로그램");
        printf("1. 연락처 추가\n");
        printf("2. 연락처 목록 보기\n");
        printf("3. 연락처 검색 (이름 일부)\n");
        printf("4. 연락처 삭제\n");
        printf("5. 전체 연락처 수 확인\n");
        printf("6. 종료\n");
        printf("\n선택: ");

        scanf("%d", &choice);
        getchar(); // 개행 제거

        switch (choice) 
        
        {
        case 1: addrecord(); break;
        case 2: listrecord(); break;
        case 3: searchrecord(); break;
        case 4: deleterecord(); break;
        case 5: countrecord(); break;
        case 6:
            printf("\n 프로그램을 종료합니다.\n");
            return 0;
        default: printf(" 잘못된 선택입니다. 다시 시도하세요.\n");
        }
        pause();
    }
    return 0;
}

int login() {
    char input[20];
    int tries = 0;

    printHeader(" 로그인 화면");

    while (tries < 3) {
        printf("비밀번호를 입력하세요: ");
        scanf("%s", input);

        if (strcmp(input, PASSWORD) == 0) return 1;

        printf(" 비밀번호가 틀렸습니다. 남은 시도: %d\n", 2 - tries);
        tries++;
    }
    return 0;
}

void addrecord() {
    FILE* fp = fopen("phonebook.txt", "a");
    struct Contact c;

    printHeader(" 연락처 추가");

    printf("이름: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("전화번호: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("이메일: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    printf("\n 저장되었습니다!\n");
}

void listrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    int count = 0;

    printHeader(" 연락처 목록");

    while (fread(&c, sizeof(c), 1, fp)) {
        printf("이름: %s\n전화: %s\n이메일: %s\n------------------\n", c.name, c.phone, c.email);
        count++;
    }

    if (count == 0)
        printf(" 저장된 연락처가 없습니다.\n");

    fclose(fp);
}

void searchrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    char search[30];
    int found = 0;

    printHeader(" 연락처 검색");

    printf("찾고 싶은 이름 일부를 입력하세요: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0;

    printf("\n 검색 결과:\n");

    while (fread(&c, sizeof(c), 1, fp))
    {
        if (strstr(c.name, search))
        {
            printf("이름: %s\n전화: %s\n이메일: %s\n------------------\n", c.name, c.phone, c.email);
            found = 1;
        }
    }

    if (!found)
        printf(" '%s' 이 포함된 연락처를 찾을 수 없습니다.\n", search);

    fclose(fp);
}

void deleterecord() 
{
    FILE* fp = fopen("phonebook.txt", "r");
    FILE* temp = fopen("temp.txt", "w");
    struct Contact c;
    char del[30];
    int found = 0;

    printHeader(" 연락처 삭제");

    printf("삭제할 이름을 입력하세요: ");
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
        printf(" '%s' 연락처가 삭제되었습니다.\n", del);
    else
        printf(" 연락처를 찾을 수 없습니다.\n");
}

void countrecord()
{
    FILE* fp = fopen("phonebook.txt", "r");
    struct Contact c;
    int count = 0;

    printHeader(" 전체 연락처 수 확인");

    if (fp == NULL) 
    {
        printf(" 파일을 열 수 없습니다.\n");
        return;
    }

    while (fread(&c, sizeof(c), 1, fp)) 
    {
        count++;
    }
    fclose(fp);

    if (count == 0)
    {
        printf(" 저장된 연락처가 없습니다.\n");
    }
    else {
        printf("총 %d개의 연락처가 저장되어 있습니다.\n", count);
    }
}

void pause() 
{
    printf("\nEnter 키를 눌러 계속하려면...\n");
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
