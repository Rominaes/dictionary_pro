#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_USERS 100
#define MAX_MEANINGS 10

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

struct DictionaryWord {
    char word[MAX_SIZE];
    char meanings[MAX_MEANINGS][MAX_SIZE];
    int meaning_count;
};

struct DictionaryNode
{
    struct DictionaryWord data;
    struct DictionaryNode *next;
};
struct DictionaryNode *dictionary_head = NULL;
int word_count = 0;



void adminMenu();
void userMenu();
void signUp();
void signIn();
void forgotPassword();
int isValidEmail(char []);
int isAlphaString(char *);
int isValidPhoneNumber(char *);
void Save_User_info(const char * , const char *);
void ReadFromFile_Admin();
void Save_words_in_file();



int main() {
    int choice = 0;
    while (choice != 4)
    {
        printf("\nLogen Page:)):\n");
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

void adminMenu() {
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
            printf("Returning to Logen Page:))...\n");
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
        Save_User_info(new_user.username , new_user.password);
    } else {
        printf("Maximum user limit reached. Cannot register new user.\n");
    }
}

void signIn() {
    int i = 0;
    char ch;
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    FILE *file;
    file = fopen("user.txt", "r");
    if (file == NULL) {
        printf("Error opening user file.\n");
        return;
    }
    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    while ((ch = getch()) != 13) {
        if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");

    char read_username[MAX_SIZE];
    char read_password[MAX_SIZE];
    int flg = 0;
    while (fscanf(file, "Username: %s\n", read_username) == 1) {
        fscanf(file, "Password: %s\n", read_password);

        if (strcmp(read_username, username) == 0 && strcmp(read_password, password) == 0) {
            printf("\nSigned in successfully.\nWelcome %s :)\n", read_username);
            flg = 1;
            break;
        }
    }
    if (!flg) {
        printf("\nInvalid username or password.\n");
    }
    fclose(file);

    login = malloc(sizeof(struct User));
    strcpy(login->username, read_username);
    if (login != NULL) {
        if (strcmp(login->username, "Admin") == 0) {
            adminMenu();
        } else {
            userMenu();
        }
    }
}

void forgotPassword() {
    int i;
    char username[MAX_SIZE];
    char phone[MAX_SIZE];
    char password[MAX_SIZE];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Phone: ");
    scanf("%s", phone);
    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].phone, phone) == 0) {
            printf("Enter New Password: ");
            scanf("%s", users[i].password);
            printf("Password updated successfully.\n");

            Save_User_info(username , password);

            return;
        }
    }
    printf("Username and phone number do not match:( \n");
}

int isValidEmail(char email[]) {
    int i , length, atIndex = -1;
    length = strlen(email);

    for ( i = 0; i < length; i++) {
        if (email[i] == '@') {
            atIndex = i;
            break;
        }
    }

    if (atIndex == -1 || atIndex > 32 || length - atIndex > 12
    || strcmp(email + length - 10, "@gmail.com") != 0)
    {return 0;}
    else
    {return 1;}
}

int isAlphaString(char *str) {
    int i;
    for ( i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]))
            {return 0;}
    }
    return 1;
}

int isValidPhoneNumber(char *phone) {
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i]))
            {return 0;}
    }
    return 1;
}

void Save_User_info(const char *username , const char *password) {
    FILE *file;
    file = fopen("user.txt", "a");
    if (file == NULL) {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Password: %s\n", password);
    fclose(file);
    printf("Login information saved successfully.\n");
}


void ReadFromFile_Admin() {
    char *token;
    char line[MAX_SIZE];
    char fileName[MAX_SIZE];
    printf("Enter File Name: ");
    scanf("%s", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File not found or could not be opened.\n");
        return;
    }
    while (fgets(line, MAX_SIZE, file) != NULL) {
        struct DictionaryNode *new_node;
        new_node = (struct DictionaryNode *)malloc(sizeof(struct DictionaryNode));
        if (new_node == NULL) {
            printf("Memory allocation failed. Cannot read from file.\n");
            fclose(file);
            return;
        }
        token = strtok(line, ",");
        if (token == NULL) {
            printf("Invalid format in file.\n");
            free(new_node);
            continue;
        }
        sscanf(token, "word: %s", new_node->data.word);
        
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Invalid format in file.\n");
            free(new_node);
            continue;
        }
        sscanf(token, " translation: %[^\n]", new_node->data.meanings[0]);
        
        new_node->data.meaning_count = 1;

        new_node->next = dictionary_head;
        dictionary_head = new_node;
        word_count++;
    }
    fclose(file);
    printf("Dictionary loaded from file successfully.\n");
}

void Save_words_in_file() {
    int count = 1;
    struct DictionaryNode *ptr;
    ptr = dictionary_head;

    FILE * file;
    file = fopen("dictionary.txt", "w");
    if (file == NULL) {
        printf("File could not be created or opened for writing.\n");
        return;
    }
    while (ptr != NULL) {
        fprintf(file, "%d- word: %s, translation: ", count, ptr->data.word);
        for (int i = 0; i < ptr->data.meaning_count; i++) {
            fprintf(file, "%s", ptr->data.meanings[i]);
            if (i != ptr->data.meaning_count - 1)
                fprintf(file, "-");
        }
        fprintf(file, "\n");
        ptr = ptr->next;
        count++;
    }

    fclose(file);
    printf("Current state saved to file successfully.\n");
}


