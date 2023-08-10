#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Data structures
struct DiaryEntry {
    char username[50];
    char date[20];
    char content[200];
};

struct User {
    char username[50];
    char password[64]; // Increased size for hashed password storage
};

// Function prototypes
void displayMenu();
void displayUserMenu(const char* username);
void registerUser();
int loginUser(char* currentUser);
void writeEntry(const char* username);
void viewEntries(const char* username);
void searchEntries(const char* username);
void clearBuffer();
void encrypt(char* text, int key);
void decrypt(char* text, int key);
bool validateDate(const char* date);
unsigned int simpleHash(const char* input);

// Constants
const char usersFileName[] = "users.txt";
const char diaryFileName[] = "diary.txt";
const int encryptionKey = 7; // Change this key for stronger encryption

int main() {
    int choice;
    char currentUser[50] = {0};
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        
        char input[50];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            exit(1);
        }
        
        // Check if the input is a valid integer
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid choice. Try again.\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(currentUser)) {
                    printf("Welcome, %s!\n", currentUser);
                    displayUserMenu(currentUser);
                } else {
                    printf("Login failed. Invalid credentials.\n");
                }
                break;
            case 3:
                printf("Exiting the application.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n========== Personal Diary Application ==========\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
}

void displayUserMenu(const char* username) {
    int choice;
    while (1) {
        printf("\n======= Logged In as %s ========\n", username);
        printf("1. Write an Entry\n");
        printf("2. View Previous Entries\n");
        printf("3. Search Entries\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        
        while (scanf("%d", &choice) != 1) {
            // Clear the invalid input
            clearBuffer();
            printf("Invalid choice. Try again.\n");
            printf("Enter your choice: ");
        }
        
        switch (choice) {
            case 1:
                writeEntry(username);
                break;
            case 2:
                viewEntries(username);
                break;
            case 3:
                searchEntries(username);
                break;
            case 4:
                printf("Logged out successfully!\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void registerUser() {
    struct User user;
    FILE* usersFile = fopen(usersFileName, "a");
    
    printf("Enter username: ");
    scanf("%s", user.username);
    clearBuffer();
    printf("Enter password: ");
    scanf("%s", user.password);
    clearBuffer();

    // Hash the password before storing
    unsigned int hashedPassword = simpleHash(user.password);
    sprintf(user.password, "%u", hashedPassword);
    
    fprintf(usersFile, "%s %s\n", user.username, user.password);
    fclose(usersFile);
    
    printf("Registration successful!\n");
}

int loginUser(char* currentUser) {
    struct User user;
    FILE* usersFile = fopen(usersFileName, "r");
    
    printf("Enter username: ");
    scanf("%s", user.username);
    clearBuffer();
    printf("Enter password: ");
    scanf("%s", user.password);
    clearBuffer();
    
    // Hash the input password for comparison
    unsigned int hashedInputPassword = simpleHash(user.password);
    sprintf(user.password, "%u", hashedInputPassword);
    
    char storedUsername[50];
    char storedPassword[64];
    
    while (fscanf(usersFile, "%s %s", storedUsername, storedPassword) == 2) {
        if (strcmp(user.username, storedUsername) == 0 && strcmp(user.password, storedPassword) == 0) {
            strcpy(currentUser, user.username);
            fclose(usersFile);
            return 1;
        }
    }
    fclose(usersFile);
    return 0;
}

void writeEntry(const char* username) {
    struct DiaryEntry entry;
    FILE* diaryFile = fopen(diaryFileName, "a");

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", entry.date);
    clearBuffer();

    while (!validateDate(entry.date)) {
        printf("Invalid date format. Please enter a valid date (DD-MM-YYYY): ");
        scanf("%s", entry.date);
        clearBuffer();
    }

    printf("Enter diary content (up to 200 characters): ");
    fgets(entry.content, sizeof(entry.content), stdin);

    // Clear the newline character from fgets
    entry.content[strcspn(entry.content, "\n")] = '\0';

    // Encrypt the diary content before writing it to the file
    encrypt(entry.content, encryptionKey);

    strcpy(entry.username, username);
    fprintf(diaryFile, "%s:%s:%s\n", entry.username, entry.date, entry.content);
    fclose(diaryFile);

    printf("Entry written successfully!\n");
}

void viewEntries(const char* username) {
    struct DiaryEntry entry;
    FILE* diaryFile = fopen(diaryFileName, "r");

    printf("===== Your Previous Entries =====\n");
    while (fscanf(diaryFile, "%[^:]:%[^:]:%[^\n]\n", entry.username, entry.date, entry.content) == 3) {
        if (strcmp(username, entry.username) == 0) {
            // Decrypt the diary content before displaying it
            decrypt(entry.content, encryptionKey);

            printf("Date: %s\nContent: %s\n\n", entry.date, entry.content);
        }
    }
    fclose(diaryFile);
}

void searchEntries(const char* username) {
    char searchTerm[50];
    struct DiaryEntry entry;
    FILE* diaryFile = fopen(diaryFileName, "r");

    printf("Enter search term (date or content): ");
    scanf("%s", searchTerm);
    clearBuffer();

    printf("===== Search Results =====\n");
    while (fscanf(diaryFile, "%[^:]:%[^:]:%[^\n]\n", entry.username, entry.date, entry.content) == 3) {
        if (strcmp(username, entry.username) == 0) {
            char decryptedContent[200];
            strcpy(decryptedContent, entry.content);

            // Decrypt the diary content for comparison
            decrypt(decryptedContent, encryptionKey);

            if (strstr(entry.date, searchTerm) || strstr(decryptedContent, searchTerm)) {
                printf("Date: %s\nContent: %s\n\n", entry.date, decryptedContent);
            }
        }
    }
    fclose(diaryFile);
}

void encrypt(char* text, int key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        text[i] = text[i] + key;
    }
}

void decrypt(char* text, int key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        text[i] = text[i] - key;
    }
}

bool validateDate(const char* date) {
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return false;
    }
    return true;
}

unsigned int simpleHash(const char* input) {
    unsigned int hash = 0;
    for (size_t i = 0; input[i] != '\0'; ++i) {
        hash += (unsigned int)input[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

