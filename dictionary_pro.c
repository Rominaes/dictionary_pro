#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

struct User {
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    char firstname[MAX_SIZE];
    char lastname[MAX_SIZE];
    char phone[MAX_SIZE];
    char email[MAX_SIZE];
};



int main()
{
    int choice = 0;
    struct User *login = NULL;
    while (choice != 4)
    {
        printf("\nMain Menu:\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Forgot Password\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            signUp();
            break;
        case 2:
            signIn();
            if (login != NULL)
            {
                if (strcmp(login->username, "Admin") == 0)
                {
                    adminMenu();
                }
                else
                {
                    userMenu();
                }
            }
            break;
        case 3:
            forgotPassword();
            break;
        case 4:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid choice, Please try again.\n");
        }
    }
    Save_words_in_file();
    return 0;
}






void adminMenu()
{
    int choice;
    while (choice != 7)
    {
        printf("\nAdmin Menu:\n");
        printf("1. Add Word\n");
        printf("2. Edit Word\n");
        printf("3. Remove Word\n");
        printf("4. Read From File\n");
        printf("5. Show All Words\n");
        printf("6. Manage Suggested Words\n");
        printf("7. Back\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            AddWord_Admin();
            break;
        case 2:
            editWord_Admin();
            break;
        case 3:
            RemoveWord_Admin();
            break;
        case 4:
            ReadFromFile_Admin();
            break;
        case 5:
            ShowAllWords_Admin();
            break;
        case 6:
            //manageSuggestedWords();
            break;
        case 7:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void userMenu() {
    int choice;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    while (choice != 6 && login != NULL)
    {
        printf("\nUser Menu:\n");
        printf("1. Search and Manage Words\n");
        printf("2. leitner box\n");
        printf("3. Test Your Knowledge\n");
        printf("4. Show Information\n");
        printf("5. Edit Information\n");
        printf("6. Log Out\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Search_User();
            levenshtein_distance_User(s1, s2);
            break;
        case 2:
            leitnerBox();
            break;
        case 3:
            Test_User();
            break;
        case 4:
            ShowInformation_User();
            break;
        case 5:
            editUserInformation();
            break;
        case 6:
            printf("Logging out...\n");
            login = NULL;
            break;
        default:
            printf("Invalid choice , Please try again.\n");
        }
    }
}



