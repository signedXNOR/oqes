#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

UCHAR * output;

unsigned int lingth = 32;
unsigned int numba = 1;

UCHAR chlib[128] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$^&*()-=[];,./_+{}|:<>?";
unsigned int currentchlibLength = 0;

void menu();
void gen();
void param();
void falloc();
void updatechlibLength();
void freeStuff();

int main(void) {
    output = malloc(lingth+1);
    updatechlibLength();
    menu();
}

void menu()
{
    printf("oqes - version windows-2.0 - TRUE RANDOM STRING GENERATOR\n");
    printf("1               - Generate string(s)\n");
    printf("2               - Set parameters\n");
    printf("Any other key   - Exit\n");
    printf("$:");
    char inp = getch();
    printf("%c\n\n", inp);
    switch(inp)
    {
        case '1':
            gen();
            menu();
            break;
        case '2':
            param();
            break;
    }
}

void gen()
{
    system("cls");
    NTSTATUS status;
    int failures = -1;
    UCHAR buff[4];
    do {
        for (int k = 0; k < 4; k++){ buff[k] = 0; }
        status = BCryptGenRandom(NULL, buff, 4, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        failures++;
    } while (status != 0);

    int randint = (intptr_t) buff;

    srand((unsigned int)randint);
    for (int j = 0; j < numba; j++)
    {
        for (unsigned int i = 0; i < lingth; i++)
        {
            char a = rand() % currentchlibLength;
            output[i] = chlib[a];
        }
        output[lingth] = '\0';
        printf("%s\n", output);
    }
}

void param()
{
    system("cls");
    printf("Which parameter would you like to modify?\n");
    printf("1               - String length\n");
    printf("2               - # of strings generated\n");
    printf("3               - String of possible characterss from which to pull when generating\n");
    printf("Any other key   - Back\n");
    printf("$:");
    char inp = getch();
    printf("\n\n");
    UCHAR buff[7];
    UCHAR buff1[128];
    switch(inp)
    {
        case '1':
            system("cls");
            printf("Default: 32\n");
            printf("Current: %d\n", lingth);
            printf("Change string length to what?\n");
            printf("$:");

            fgets(buff, 7, stdin);
            if (buff[0] != '\n')
            {
                lingth = (unsigned int)atoi(buff);
                output = realloc(output, lingth-1);
                printf("String length is now %d ", lingth);
            } else {
                printf("String length remains unchanged ");
            }
            
            getch();
            param();
            break;
        case '2':
            system("cls");
            printf("Default: 1\n");
            printf("Current: %d\n", numba);
            printf("Change string number to what?\n");
            printf("$:");

            fgets(buff, 7, stdin);
            if (buff[0] != '\n') {
                numba = (unsigned int)atoi(buff);
                printf("Number of strings generated is now %d ", numba);
            } else {
                printf("Number of strings remains unchanged ");
            }

            getch();
            param();
            break;
        case '3':
            system("cls");
            printf("Default: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$^&*()-=[];,./_+{}|:<>?\n");
            printf("Current: %s\n", chlib);
            printf("Change pool of possible characters to what?\n");
            printf("$:");

            fgets(buff1, 128, stdin);
            buff1[strcspn(buff1, "\n")] = '\0';
            if (buff1[0] != '\n') {
                memcpy(chlib, buff1, 128);
                printf("Character pool is now %s\n", chlib);
                updatechlibLength();
            } else {
                printf("Character pool remains unchanged ");
            }

            getch();
            param();
            break;
        default:
            system("cls");
            menu();
    }
}

void updatechlibLength()
{
    currentchlibLength = 0;
    for (int j = 0; j<100; j++)
    {
        if (chlib[j] == '\0')
        {
            break;
        } else { currentchlibLength++; }
    }
}

void freeStuff()
{
    free(output);
    output = NULL;
}