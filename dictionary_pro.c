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





