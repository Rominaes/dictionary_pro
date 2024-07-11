#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_USERS 100

struct User
{
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    char firstname[MAX_SIZE];
    char lastname[MAX_SIZE];
    char phone[MAX_SIZE];
    char email[MAX_SIZE];
};
struct User *login = NULL;
struct User users[MAX_USERS];
int user_count = 0;



int main()
{
    int choice = 0;
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
            // manageSuggestedWords();
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

void signUp() {
    struct User new_user;
    printf("Enter First Name: ");
    scanf("%s", new_user.firstname);
    if (strlen(new_user.firstname) == 0) {
        printf("First name cannot be empty.\n");
        return;
    }
    if (isAlphaString(new_user.firstname) == 0) {
        printf("First name must contain only alphabetic characters.\n");
        return;
    }

    printf("Enter Last Name: ");
    scanf("%s", new_user.lastname);
    if (strlen(new_user.lastname) == 0) {
        printf("Last name cannot be empty.\n");
        return;
    }
    if (isAlphaString(new_user.lastname) == 0) {
        printf("Last name must contain only alphabetic characters.\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%s", new_user.username);
    if (strlen(new_user.username) == 0) {
        printf("Username cannot be empty.\n");
        return;
    }
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, new_user.username) == 0) {
            printf("Username already exists. Please choose another one.\n");
            return;
        }
    }

    printf("Enter Password: ");
    scanf("%s", new_user.password);

    printf("Enter Phone: ");
    scanf("%s", new_user.phone);
    if (!isValidPhoneNumber(new_user.phone)) {
        printf("Phone number must contain only digits.\n");
        return;
    }

    printf("Enter Email: ");
    scanf("%s", new_user.email);
    if (isValidEmail(new_user.email) == 0) {
        printf("Invalid email format.\n");
        return;
    }

    if (user_count < MAX_USERS) {
        strcpy(users[user_count].firstname, new_user.firstname);
        strcpy(users[user_count].lastname, new_user.lastname);
        strcpy(users[user_count].username, new_user.username);
        strcpy(users[user_count].password, new_user.password);
        strcpy(users[user_count].phone, new_user.phone);
        strcpy(users[user_count].email, new_user.email);
        user_count++;
        printf("User registered successfully.\n");
        Save_User_info(new_user.username);
    } else {
        printf("Maximum user limit reached. Cannot register new user.\n");
    }
}

void signIn() {
    int i = 0;
    char ch;
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    while ((ch = getchar()) != '\n' && ch != EOF);
    i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        password[i++] = ch;
    }
    password[i] = '\0';
    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            login = &users[i];
            printf("Signed in successfully.\nWelcome, %s:)\n", login->firstname);
            
            Save_User_info(username);

            return;
        }
    }
    printf("Invalid username or password.\n");
}

