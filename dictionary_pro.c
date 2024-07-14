#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable:4996)

#define MAX_SIZE 100
#define MAX_USERS 100
#define MAX_MEANINGS 10
#define MAX_WORDS 100
#define LINE_SIZE 100
#define WORD_SIZE 50
#define MAX_SUGGESTED_WORDS 100
#define MAX_LEARNED_WORDS 100

struct User
{
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    char firstname[MAX_SIZE];
    char lastname[MAX_SIZE];
    char phone[MAX_SIZE];
    char email[MAX_SIZE];
};
struct User* login = NULL;
struct User users[MAX_USERS];
int user_count = 0;

struct Words
{
    char word[MAX_SIZE]; 
    char meanings[MAX_MEANINGS][MAX_SIZE]; 
    int meaning_count;  
};

struct Node 
{
    struct Words data;
    struct Node* next; 
};
struct Node* dictionary_head = NULL;


void adminMenu();
void userMenu();

void AddWord_Admin();
void editWord_Admin();
void RemoveWord_Admin();
void ReadFromFile_Admin();
void ShowAllWords_Admin();
void signUp();
void signIn();
void forgotPassword();
int isValidEmail(char[]);
int isAlphaString(char*);
int isValidPhoneNumber(char*);
void Save_User_info(const char*, const char*);


void insert(struct Node** head, Words data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data.word, data.word);
    for (int i = 0;i<data.meaning_count; i++)
    {
        strcpy(newNode->data.meanings[i], data.meanings[i]);
    }
    if (*head == NULL)
    {
        *head = newNode;
        (*head)->next = NULL;
        return;
    }
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void deleteNode(struct Node** head, Words data)
{
    if (*head == NULL)
    {
        printf("there is no words\n");
        return;
    }
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (strcmp(temp->data.word, data.word) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->data.word, data.word) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("This word is not in dictionary!!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void creatLinkedlist(struct Node** head, const char* Filename);
void Save_words_in_file(struct Node** head, const char* Filename);



int main()
{
    creatLinkedlist(&dictionary_head, "dictionary.txt"); 
    int choice = 0;
    while (choice != 4)
    {
        printf("\nLogen Page:))\n");
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
            printf("Returning to Login Page:))...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
        Save_words_in_file(&dictionary_head, "dictionary.txt");
    }
}

void userMenu() 
{
    struct Node* Litner_head = NULL; 
    struct Node* newWords_head = NULL; 
    struct Node* reviewWords_head = NULL;
    struct Node* consolidationWords_head = NULL;
    struct Node* learnedWords_head = NULL;
    
    char fname1[20];
    strcpy(fname1, login->username);
    strcat(fname1, "$Litner");
    creatLinkedlist(&Litner_head, fname1);
    
    char fname2[20];
    strcpy(fname2, login->username);
    strcat(fname2, "$NewWord");
    creatLinkedlist(&newWords_head, fname2);
    
    char fname3[20];
    strcpy(fname3, login->username);
    strcat(fname3, "$Review");
    creatLinkedlist(&reviewWords_head, fname3);
    
    char fname4[20];
    strcpy(fname4, login->username);
    strcat(fname4, "$Consolidationhead");
    creatLinkedlist(&consolidationWords_head, fname4);
    
    char fname5[20];
    strcpy(fname5, login->username);
    strcat(fname5, "$Learned");
    creatLinkedlist(&learnedWords_head, fname5);
    int choice;
    struct Words words[MAX_WORDS];
    int word_count = 0;

    while (choice != 6 && login != NULL)
    {
        printf("\nUser Menu:\n");
        printf("1. Search and Manage Words\n");
        printf("2. Leitner Box\n");
        printf("3. Test Your Knowledge\n");
        printf("4. Show Information\n");
        printf("5. Edit Information\n");
        printf("6. Log Out\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            //readWordsFromFile(words, &word_count);
            searchWord(words, word_count);
            break;
        case 2:
            leitnerBox(&Litner_head, &newWords_head, &reviewWords_head, &consolidationWords_head, &learnedWords_head); 
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
            printf("Invalid choice, Please try again.\n");
        }
        Save_words_in_file(&dictionary_head, "dictionary.txt");
        Save_words_in_file(&Litner_head, fname1);
        Save_words_in_file(&newWords_head, fname2);
        Save_words_in_file(&reviewWords_head, fname3);
        Save_words_in_file(&consolidationWords_head, fname4);
        Save_words_in_file(&learnedWords_head, fname5);
    }
}


void signUp()
{
    struct User new_user;
    printf("Enter First Name: ");
    scanf("%s", new_user.firstname);
    if (strlen(new_user.firstname) == 0)
    {
        printf("First name cannot be empty.\n");
        return;
    }
    if (isAlphaString(new_user.firstname) == 0)
    {
        printf("First name must contain only alphabetic characters.\n");
        return;
    }

    printf("Enter Last Name: ");
    scanf("%s", new_user.lastname);
    if (strlen(new_user.lastname) == 0)
    {
        printf("Last name cannot be empty.\n");
        return;
    }
    if (isAlphaString(new_user.lastname) == 0)
    {
        printf("Last name must contain only alphabetic characters.\n");
        return;
    }

    printf("Enter Username: ");
    scanf("%s", new_user.username);
    if (strlen(new_user.username) == 0)
    {
        printf("Username cannot be empty.\n");
        return;
    }
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, new_user.username) == 0)
        {
            printf("Username already exists. Please choose another one.\n");
            return;
        }
    }

    printf("Enter Password: ");
    scanf("%s", new_user.password);

    printf("Enter Phone: ");
    scanf("%s", new_user.phone);
    if (!isValidPhoneNumber(new_user.phone))
    {
        printf("Phone number must contain only digits.\n");
        return;
    }

    printf("Enter Email: ");
    scanf("%s", new_user.email);
    if (isValidEmail(new_user.email) == 0)
    {
        printf("Invalid email format.\n");
        return;
    }

    if (user_count < MAX_USERS)
    {
        strcpy(users[user_count].firstname, new_user.firstname);
        strcpy(users[user_count].lastname, new_user.lastname);
        strcpy(users[user_count].username, new_user.username);
        strcpy(users[user_count].password, new_user.password);
        strcpy(users[user_count].phone, new_user.phone);
        strcpy(users[user_count].email, new_user.email);
        user_count++;
        printf("User registered successfully.\n");
        Save_User_info(new_user.username, new_user.password);
    }
    else
    {
        printf("Maximum user limit reached. Cannot register new user.\n");
    }
}

void signIn()
{
    int i = 0;
    char ch;
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    FILE* file;
    file = fopen("user.txt", "r");
    if (file == NULL)
    {
        printf("Error opening user file.\n");
        return;
    }
    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    while ((ch = getch()) != 13)
    {
        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");

    char read_username[MAX_SIZE];
    char read_password[MAX_SIZE];
    int flg = 0;
    while (fscanf(file, "Username: %s\n", read_username) == 1)
    {
        fscanf(file, "Password: %s\n", read_password);

        if (strcmp(read_username, username) == 0 && strcmp(read_password, password) == 0)
        {
            printf("\nSigned in successfully.\nWelcome %s :)\n", read_username);
            flg = 1;
            break;
        }
    }
    if (!flg)
    {
        printf("\nInvalid username or password.\n");
    }
    else
    {
        login = (User*)malloc(sizeof(struct User));
        strcpy(login->username, read_username);
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
    }
    fclose(file);
}

void forgotPassword()
{
    int i;
    char username[MAX_SIZE];
    char phone[MAX_SIZE];
    char password[MAX_SIZE];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Phone: ");
    scanf("%s", phone);
    for (i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].phone, phone) == 0)
        {
            printf("Enter New Password: ");
            scanf("%s", users[i].password);
            printf("Password updated successfully.\n");

            Save_User_info(username, password);

            return;
        }
    }
    printf("Username and phone number do not match:( \n");
}

int isValidEmail(char email[])
{
    int i, length, atIndex = -1;
    length = strlen(email);

    for (i = 0; i < length; i++)
    {
        if (email[i] == '@')
        {
            atIndex = i;
            break;
        }
    }

    if (atIndex == -1 || atIndex > 32 || length - atIndex > 12 || strcmp(email + length - 10, "@gmail.com") != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int isAlphaString(char* str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int isValidPhoneNumber(char* phone)
{
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }
    return 1;
}

void Save_User_info(const char* username, const char* password)
{
    FILE* file;
    file = fopen("user.txt", "a");
    if (file == NULL)
    {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Password: %s\n", password);
    fclose(file);
    printf("Login information saved successfully.\n");
}


void AddWord_Admin()
{
    struct Node* ptr;
    struct Node* new_node;
    new_node = (struct Node*)malloc(sizeof(struct Node));

    if (strcmp(login->username, "Admin") != 0)
    {
        printf("You do not have permission to add words.\n");
        return;
    }

    if (new_node == NULL)
    {
        printf("Memory allocation failed. Cannot add new word.\n");
        return;
    }
    printf("Enter Word: ");
    scanf("%s", new_node->data.word);
    for (ptr = dictionary_head; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->data.word, new_node->data.word) == 0)
        {
            printf("Word already exists. You can edit the word instead.\n");
            free(new_node);
            return;
        }
    }
    new_node->data.meaning_count = 0;
    while (new_node->data.meaning_count < MAX_MEANINGS)
    {
        printf("Enter Meaning (or 'stop' to finish): ");
        scanf("%s", new_node->data.meanings[new_node->data.meaning_count]);
        if (strcmp(new_node->data.meanings[new_node->data.meaning_count], "stop") == 0)
        {
            break;
        }
        new_node->data.meaning_count++;
    }
    new_node->next = dictionary_head;
    dictionary_head = new_node;
    printf("Word added successfully.\n");
    Save_words_in_file();
}

void editWord_Admin()
{
    int choice;
    int found = 0;
    char word[MAX_SIZE];
    char meaning[MAX_SIZE];
    struct Node* ptr;
    ptr = dictionary_head;
    if (strcmp(login->username, "Admin") != 0)
    {
        printf("You do not have permission to edit words.\n");
        return;
    }
    printf("Enter Word to Edit: ");
    scanf("%s", word);
    while (ptr != NULL)
    {
        if (strcmp(ptr->data.word, word) == 0)
        {
            while (choice != 4)
            {
                printf("1. Add Meaning\n");
                printf("2. Remove Meaning\n");
                printf("3. Edit Meaning\n");
                printf("4. Exit\n");
                printf("Choose an option: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    if (ptr->data.meaning_count < MAX_MEANINGS)
                    {
                        printf("Enter New Meaning: ");
                        scanf("%s", ptr->data.meanings[ptr->data.meaning_count]);
                        ptr->data.meaning_count++;
                        printf("Meaning added successfully.\n");
                    }
                    else
                    {
                        printf("Maximum meanings limit reached for this word.\n");
                    }
                    break;
                case 2:
                    if (ptr->data.meaning_count > 0)
                    {
                        printf("Enter Meaning to Remove: ");
                        scanf("%s", meaning);
                        for (int j = 0; j < ptr->data.meaning_count; j++)
                        {
                            if (strcmp(ptr->data.meanings[j], meaning) == 0)
                            {
                                found = 1;
                                for (int k = j; k < ptr->data.meaning_count - 1; k++)
                                {
                                    strcpy(ptr->data.meanings[k], ptr->data.meanings[k + 1]);
                                }
                                ptr->data.meaning_count--;
                                printf("Meaning removed successfully.\n");
                                break;
                            }
                        }
                        if (!found)
                        {
                            printf("Meaning not found for this word.\n");
                        }
                    }
                    else
                    {
                        printf("No meanings.\n");
                    }
                    break;
                case 3:
                    if (ptr->data.meaning_count > 0)
                    {
                        int found2 = 0;
                        char old_meaning[MAX_SIZE];
                        char new_meaning[MAX_SIZE];
                        printf("Enter Meaning to Edit: ");
                        scanf("%s", old_meaning);
                        printf("Enter New Meaning: ");
                        scanf("%s", new_meaning);
                        for (int j = 0; j < ptr->data.meaning_count; j++)
                        {
                            if (strcmp(ptr->data.meanings[j], old_meaning) == 0)
                            {
                                strcpy(ptr->data.meanings[j], new_meaning);
                                found2 = 1;
                                printf("Meaning edited successfully.\n");
                                break;
                            }
                        }
                        if (!found2)
                        {
                            printf("Meaning not found for this word.\n");
                        }
                    }
                    else
                    {
                        printf("No meanings.\n");
                    }
                    break;
                case 4:
                    printf("Returning to admin menu...\n");
                    break;
                default:
                    printf("Invalid choice , Please try again.\n");
                }
                Save_words_in_file(&dictionary_head, "dictionary.txt");
            }
            return;
        }
        ptr = ptr->next;
    }
    printf("Word not found:(\n");
}

void RemoveWord_Admin()
{
    char word[MAX_SIZE];
    struct Node* prev = NULL;
    struct Node* curr = dictionary_head;
    if (strcmp(login->username, "Admin") != 0)
    {
        printf("You do not have permission to remove words.\n");
        return;
    }
    printf("Enter Word to Remove: ");
    scanf("%s", word);
    while (curr != NULL)
    {
        if (strcmp(curr->data.word, word) == 0)
        {
            if (prev == NULL)
            {
                dictionary_head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            
            printf("Word removed successfully.\n");
            Save_words_in_file();
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Word not found.\n");
}

void ShowAllWords_Admin()
{
    int count = 0;
    char initial;
    char currentInitial;
    struct Node* ptr;
    struct Node* temp;
    struct Node* wordsArray[MAX_SIZE];
    ptr = dictionary_head;
    while (ptr != NULL)
    {
        wordsArray[count++] = ptr;
        ptr = ptr->next;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (strcmp(wordsArray[j]->data.word, wordsArray[j + 1]->data.word) > 0)
            {
                temp = wordsArray[j];
                wordsArray[j] = wordsArray[j + 1];
                wordsArray[j + 1] = temp;
            }
        }
    }

    printf("\nDictionary Words:\n");
    currentInitial = '\0';
    for (int i = 0; i < count; i++)
    {
        initial = toupper(wordsArray[i]->data.word[0]);
        if (initial != currentInitial)
        {
            currentInitial = initial;
            printf("\n%c:\n", currentInitial);
        }
        printf("  Word: %s\n", wordsArray[i]->data.word);
        for (int j = 0; j < wordsArray[i]->data.meaning_count; j++)
        {
            printf("    Meaning %d: %s\n", j + 1, wordsArray[i]->data.meanings[j]);
        }
    }
}

void ReadFromFile_Admin()
{
    char* token;
    char line[MAX_SIZE];
    char fileName[MAX_SIZE];
    printf("Enter File Name: ");
    scanf("%s", fileName);
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("File not found or could not be opened.\n");
        return;
    }
    while (fgets(line, MAX_SIZE, file) != NULL)
    {
        struct Node* new_node;
        new_node = (struct Node*)malloc(sizeof(struct Node));
        if (new_node == NULL)
        {
            printf("Memory allocation failed. Cannot read from file.\n");
            fclose(file);
            return;
        }
        token = strtok(line, ",");
        if (token == NULL)
        {
            printf("Invalid format in file.\n");
            free(new_node);
            continue;
        }
        sscanf(token, "word: %s", new_node->data.word);

        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("Invalid format in file.\n");
            free(new_node);
            continue;
        }
        sscanf(token, " translation: %[^\n]", new_node->data.meanings[0]);

        new_node->data.meaning_count = 1;

        new_node->next = dictionary_head;
        dictionary_head = new_node;
    }
    fclose(file);
    printf("Dictionary loaded from file successfully.\n");
}
